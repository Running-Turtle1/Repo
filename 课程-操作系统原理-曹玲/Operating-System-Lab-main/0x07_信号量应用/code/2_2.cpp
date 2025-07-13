#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PATIENTS 25
#define NUM_DOCTORS 3
#define WAITING_ROOM_CAPACITY 20

sem_t waiting_room;     // 候诊室空位信号量
sem_t patients_ready;   // 准备看病的病人数
sem_t mutex;            // 对候诊室队列的互斥操作
sem_t doctor;           // 医生资源信号量
sem_t being_treated;  // 医生和病人之间的看病同步信号量

void* patient(void* arg) {
    long id = (long)arg;

    sem_wait(&waiting_room);      // 等待候诊室有空位
    sem_wait(&mutex);             // 进入临界区
    printf("Patient %ld entered waiting room\n", id);
    sem_post(&patients_ready);    // 通知医生有病人准备看病
    sem_post(&mutex);             // 离开临界区
    
    sem_wait(&doctor);            // 等待医生空闲
    sem_wait(&being_treated);     // 等待医生叫号
    printf("Patient %ld is seeing the doctor\n", id);
    sem_post(&waiting_room);      // 释放候诊室空位
    return NULL;
}


void* doctor_thread(void* arg) {
    long id = (long)arg;

    while (1) {
        sem_wait(&patients_ready);  // 等待病人准备好
        sem_wait(&mutex);           // 进入临界区
        printf("Doctor %ld is calling a patient\n", id);
        sem_post(&being_treated);   // 通知病人可以看病
        sem_post(&mutex);           // 离开临界区

        sem_post(&doctor);          // 医生资源增加，准备看病
        printf("Doctor %ld is seeing a patient\n", id);
        sleep(1);                   // 模拟看病时间
    }
    return NULL;
}


int main() {
    pthread_t patients[NUM_PATIENTS];
    pthread_t doctors[NUM_DOCTORS];

    // 初始化信号量
    sem_init(&waiting_room, 0, WAITING_ROOM_CAPACITY);
    sem_init(&patients_ready, 0, 0);
    sem_init(&mutex, 0, 1);
    sem_init(&doctor, 0, NUM_DOCTORS);
    sem_init(&being_treated, 0, 0);

    // 创建医生线程
    for (long i = 0; i < NUM_DOCTORS; i++) {
        pthread_create(&doctors[i], NULL, doctor_thread, (void*)i);
    }

    // 创建病人线程
    for (long i = 0; i < NUM_PATIENTS; i++) {
        pthread_create(&patients[i], NULL, patient, (void*)i);
        sleep(rand() % 2); // 病人到达的间隔时间
    }

    // 等待病人线程结束
    for (int i = 0; i < NUM_PATIENTS; i++) {
        pthread_join(patients[i], NULL);
    }

    // 杀死医生线程
    for (int i = 0; i < NUM_DOCTORS; i++) {
        pthread_cancel(doctors[i]);
    }

    // 销毁信号量
    sem_destroy(&waiting_room);
    sem_destroy(&patients_ready);
    sem_destroy(&mutex);
    sem_destroy(&doctor);
    sem_destroy(&being_treated);

    return 0;
}
