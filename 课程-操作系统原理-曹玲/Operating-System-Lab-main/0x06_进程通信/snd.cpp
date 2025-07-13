#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 100

struct message
{
	long msg_type;
	char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // 生成唯一的键值
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    // 获取用户输入并发送消息
    printf("请输入消息: ");
    fgets(msg.msg_text, MAX_MSG_SIZE, stdin);
    msg.msg_type = 1;

    // 将消息发送给服务器
    msgsnd(msgid, &msg, sizeof(msg), 0);
    printf("消息已发送到服务器。\n");

    // 接收服务器的响应
    msgrcv(msgid, &msg, sizeof(msg), 2, 0);
    printf("服务器响应: %s\n", msg.msg_text);

    return 0;
}