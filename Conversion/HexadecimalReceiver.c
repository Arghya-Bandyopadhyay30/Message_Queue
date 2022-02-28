#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/msg.h>

struct my_msgbuf {
	long mtype;
	char mtext[100];
}message;

int main() {
	int msgid = msgget((key_t)123, 0666|IPC_CREAT);
	msgrcv(msgid, &message, sizeof(message), 1, 0);
	printf("Hexadecimal Value Received = %s\n", message.mtext);
}
