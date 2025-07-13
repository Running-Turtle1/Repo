#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

#define BUFFER_SIZE 5 // 缓冲区大小
#define PRODUCE_COUNT 15

int buffer[BUFFER_SIZE];
int in = 0, out = 0; // 生产者写入和消费者读取位置
int produce_done = 0; // 是否完成生产

sem_t empty; // 信号量：表示缓冲区空闲位置数
sem_t full; // 信号量：表示缓冲区资源数
pthread_mutex_t mutex; // 互斥锁, 保护缓冲区

void* producer(void* arg) {
	for(int i = 0; i < PRODUCE_COUNT; i ++) {
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);

		int x;
		cout << "请输入生产者数据: \n";
		cin >> x; // 读入数据
		buffer[in] = x;
		printf("Producer: Produced %d at position %d\n", buffer[in], in);
		in = (in + 1) % BUFFER_SIZE;

		pthread_mutex_unlock(&mutex);
		sem_post(&full);

		sleep(1);  // 模拟生产时间
	}

	/* 标记生产者完成 */
    pthread_mutex_lock(&mutex);
    produce_done = 1;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* consumer(void* arg) {
	while(1) {
		pthread_mutex_lock(&mutex);
		if(produce_done && (in == out)) {
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);

		sem_wait(&full);
		pthread_mutex_lock(&mutex);

		int item = buffer[out];
		printf("Consumer: Consumed %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;  // 环形缓冲区

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(2);
	}

	return NULL;
}

int main() {
	pthread_t prod_thread, cons_thread;

	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
 
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
 
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
