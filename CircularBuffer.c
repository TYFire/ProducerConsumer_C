#include <stdio.h>
#include <string.h>

#define QUEUE_SIZE 5 // real size is -1 

typedef struct{
	int dct[QUEUE_SIZE];
	int cp; //consumer pointer, first
	int pp; //producer pointer, second
} CircularBuffer, * CB_Pointer; //

void InitQueue(CB_Pointer cbp){
	memset(cbp, 0, sizeof(*cbp));
}

void EnterQueue(CB_Pointer cbp, int val){
	if(IsFull(cbp)){
		printf("Queue %p is full!\n", cbp);
		return;
	}
	cbp->dct[cbp->pp] = val;
	cbp->pp = (cbp->pp + 1) % QUEUE_SIZE;
	return;
}


int LeaveQueue(CB_Pointer cbp){
	if(IsEmpty(cbp)){
		printf("Queue %p is empty!\n", cbp);
		return -1;
	}
	int tmp = cbp->dct[cbp->cp];
	cbp->cp = (cbp->cp + 1) % QUEUE_SIZE;
	return tmp;
}


void DisplayQueue(CB_Pointer cbp){
	if(IsEmpty(cbp)){
		printf("Queue %p is empty\n", cbp);
		return;
	}
	printf("Queue elements: ");
	int p1 = cbp->cp;
	int p2 = cbp->pp;
	while(p1 != p2){
		printf("%d ", cbp->dct[p1]);
		p1 = (p1 + 1) % QUEUE_SIZE;
	}
	printf("\n");
}


int IsFull(CB_Pointer cbp){
	return (cbp->pp + 1) % QUEUE_SIZE == cbp->cp;
}


int IsEmpty(CB_Pointer cbp){
	return cbp->cp == cbp->pp;
}

int QueueNum(CB_Pointer cbp){
	int p1 = cbp->cp;
	int p2 = cbp->pp;
	int num = 0;
	while(p1 != p2){
		p1 = (p1 + 1) % QUEUE_SIZE;
		num++;
	}
	return num;
}

int QueueSize(CB_Pointer cbp){
	return QUEUE_SIZE - 1;
}