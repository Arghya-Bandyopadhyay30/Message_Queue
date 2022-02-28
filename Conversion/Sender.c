#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/msg.h>

struct my_msgbuf {
	long mtype;
	char mtext[100];
}message;

char* decToHex(int num) {
	char *hex = malloc(sizeof(char)*100);
	sprintf(hex, "%X", num);
	return hex;
}

char* decToOct(int num) {
	char *oct = malloc(sizeof(char)*100);
	sprintf(oct, "%o", num);
	return oct;
}

char* decToBin(int num) {
	char *bin = malloc(sizeof(char)*32);
	int i,j;
	for(i=31, j=0; i>=0; j++, i--) {
		int k = num >> i;
		if(k & 1)
			bin[j] = '1';
		else
			bin[j] = '0';
	}
	return bin;
}


int main() {
	int msgid = msgget((key_t)123, 0666|IPC_CREAT);
	 message.mtype = 1;

	int num;
	printf("Enter a Decimal Number: ");
	scanf("%d", &num);
	
	char *hex = decToHex(num);
	strcpy(message.mtext, hex);
	msgsnd(msgid, &message, sizeof(message), 0);
	printf("\nData is sent to HexadecimalReceiver.c File\n\n");
	
	char *oct = decToOct(num);
	strcpy(message.mtext, oct);
	msgsnd(msgid, &message, sizeof(message), 0);
	printf("Data is sent to OctalReceiver.c File\n\n");
	
	char *bin = decToBin(num);
	strcpy(message.mtext, bin);
	msgsnd(msgid, &message, sizeof(message), 0);
	printf("Data is sent to BinaryReceiver.c File\n\n");
}
