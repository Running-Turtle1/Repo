#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define MAX_MSG_SIZE 100

struct message {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int msgid;

void handle_signal(int sig) { // 处理 CTRL+C 信号并清理消息队列的函数
    msgctl(msgid, IPC_RMID, NULL);
    printf("\n消息队列已删除。退出...\n");
    exit(0);
}

int main() {
    key_t key;
    struct message msg;

    signal(SIGINT, handle_signal);  

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("服务器正在运行... 按 CTRL+C 停止。\n");


    int cnt = 0;
    while (1) { // 服务器循环，接收消息并做出响应
        char resp[MAX_MSG_SIZE] = "server received, and this is the ";
        msgrcv(msgid, &msg, sizeof(msg), 1, 0);
        printf("收到消息: %s\n", msg.msg_text);

        sprintf(s + strlen(s), "%d", ++ cnt);
        strcat(s, " message that server has received !");
        strcpy(msg.msg_text, "server received!");
        msg.msg_type = 2;

        msgsnd(msgid, &msg, sizeof(msg), 0);
    }

    return 0;
}
