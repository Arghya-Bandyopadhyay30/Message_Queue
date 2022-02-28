#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>

struct my_msgbuf {
	long mtype;
	char mtext[100];
};

void Merge(char* arr[],int low,int mid,int high) {
	int nL= mid-low+1;
	int nR= high-mid;

	char** L=malloc(sizeof(char *)*nL);
	char** R=malloc(sizeof(char *)*nR);
    	
    	int i;
    	for(i=0; i<nL; i++) {
        	L[i]=malloc(sizeof(arr[low+i]));
        	strcpy(L[i],arr[low+i]);
    	}
    
    	for(i=0; i<nR; i++) {
		R[i]=malloc(sizeof(arr[mid+i+1]));
		strcpy(R[i],arr[mid+i+1]);
	}
    
    	int j=0, k;
    	i=0;
    	k=low;
    
    	while(i<nL && j<nR) {
		if(strcmp(L[i],R[j])<0) strcpy(arr[k++],L[i++]);
		else strcpy(arr[k++],R[j++]);
    	}
    	
    	while(i<nL) strcpy(arr[k++],L[i++]);
    	while(j<nR) strcpy(arr[k++],R[j++]);
}


void MergeSort(char* arr[],int low,int high) {
	if(low<high) {
		int mid=(low+high)/2;
		MergeSort(arr,low,mid);
		MergeSort(arr,mid+1,high);
		Merge(arr,low,mid,high);
	}
}

int main() {
	int msgid2 = msgget((key_t)234, 0666|IPC_CREAT);
	struct my_msgbuf Number;
	msgrcv(msgid2, &Number, sizeof(Number), 1, 0);
	
	int temp = atoi(Number.mtext);
	struct my_msgbuf Roll[temp];
	msgrcv(msgid2, &Roll, sizeof(Roll), 3, 0);
	
	char** arr= malloc(sizeof(char*)*temp);
	int i;
    	for(i=0; i<temp; i++) {
        	arr[i]=malloc(sizeof(char)*10);
        	strcpy(arr[i], Roll[i].mtext);
    	}
	MergeSort(arr, 0, temp-1);
	
	printf("Sorted Order Roll:\n");
	for(int i=0; i<temp; i++) {
		strcpy(Roll[i].mtext, arr[i]);
		printf("%s\n", Roll[i].mtext);
	}
	
	msgctl(msgid2, IPC_RMID, NULL);
	
	int msgid4 = msgget((key_t)456, 0666|IPC_CREAT);
	for(int i=0; i<temp; i++) {
		Roll[i].mtype = 5;
	}
	msgsnd(msgid4, &Roll, sizeof(Roll), 0);
}
