#include "CircularBuffer.c"

int main(void){
	int i = 0;
	CircularBuffer cb;
	InitQueue(&cb);
	for(i = 0; i < 10; i++){
		EnterQueue(&cb, i);
	}

	for(i = 0; i < 10; i++){
		printf("%d\n", LeaveQueue(&cb));
	}
	return 0;
}
