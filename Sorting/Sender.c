#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>

struct my_msgbuf {
	long mtype;
	char mtext[100];
};

int main() {
	char *num = malloc(sizeof(char)*10);
	printf("Enter the number of Students: ");
	scanf("%s",num);
	
	int msgid1 = msgget((key_t)123, 0666|IPC_CREAT);
	int msgid2 = msgget((key_t)234, 0666|IPC_CREAT);
	
	int temp = atoi(num);
	
	struct my_msgbuf Number;
	Number.mtype = 1;
	strcpy(Number.mtext, num);
	msgsnd(msgid1, &Number, sizeof(Number), 0);
	msgsnd(msgid2, &Number, sizeof(Number), 0);
	
	struct my_msgbuf Name[temp];
	struct my_msgbuf Roll[temp];
	
	printf("Enter the Names and Roll Numbers:\n");
	for(int i=0; i<temp; i++) {
		Name[i].mtype = 2;
		Roll[i].mtype = 3;
		
		scanf("%s %s", Name[i].mtext,Roll[i].mtext);
	}
	msgsnd(msgid1, &Name, sizeof(Name), 0);
	msgsnd(msgid2, &Roll, sizeof(Roll), 0);
	
	int msgid3 = msgget((key_t)345, 0666|IPC_CREAT);
	int msgid4 = msgget((key_t)456, 0666|IPC_CREAT);
	
	msgrcv(msgid3, &Name, sizeof(Name), 4, 0);
	msgrcv(msgid4, &Roll, sizeof(Roll), 5, 0);
	
	printf("\nSorted Recorded:\n");
	for(int i=0; i<temp; i++) {
		printf("%s: %s\n", Name[i].mtext, Roll[i].mtext);
	}
	
	msgctl(msgid3, IPC_RMID, NULL);
	msgctl(msgid4, IPC_RMID, NULL);
}

/*
Ronit 43
Ayushi 35
Shreyashi 54
Arghya 28
Ayandip 32
*/
