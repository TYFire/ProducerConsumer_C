#include "CircularBuffer.c"

static CircularBuffer gtQueue;
int main(void)
{
    InitQueue(&gtQueue);
    printf("Enter Queue 1,2,3,4,5...\n");
    EnterQueue(&gtQueue, 1);
    EnterQueue(&gtQueue, 2);
    EnterQueue(&gtQueue, 3);
    EnterQueue(&gtQueue, 4);
    EnterQueue(&gtQueue, 5);
    printf("Queue Status: Empty(%d), Full(%d)\n", IsEmpty(&gtQueue), IsFull(&gtQueue));
    //printf("Queue Elem Num: %u\n", QueDataNum(&gtQueue));
    //printf("Head: %u(%d)\n", GetQueHead(&gtQueue), GetQueHeadData(&gtQueue));
    //printf("Tail: %u\n", GetQueTail(&gtQueue));
    DisplayQueue(&gtQueue);

    printf("\nLeave Queue...\n");
    printf("Leave %d\n", LeaveQueue(&gtQueue));
    printf("Leave %d\n", LeaveQueue(&gtQueue));
    printf("Leave %d\n", LeaveQueue(&gtQueue));
    DisplayQueue(&gtQueue);

    printf("\nEnter Queue 6,7...\n");
    EnterQueue(&gtQueue, 6);
    EnterQueue(&gtQueue, 7);
    DisplayQueue(&gtQueue);

    printf("\nLeave Queue...\n");
    printf("Leave %d\n", LeaveQueue(&gtQueue));
    printf("Leave %d\n", LeaveQueue(&gtQueue));
    printf("Leave %d\n", LeaveQueue(&gtQueue));
    DisplayQueue(&gtQueue);
}
