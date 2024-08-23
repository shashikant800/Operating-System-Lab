#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct PCB{
    int process_id;
    int priority;
    char state[20];
    struct PCB* next;

}PCB;

typedef struct ReadyQueue{
    PCB* front;
    PCB* rear;
}ReadyQueue;

PCB* createPCB(int process_id, int priority, const char* state){
    PCB* newPCB= (PCB*)malloc(sizeof(PCB));
    newPCB->process_id=process_id;
    newPCB->priority = priority;
    strcpy(newPCB->state,state);
    newPCB->next = NULL;
    return newPCB;
}

void initReadyQueue(ReadyQueue* queue){
    queue->front = NULL;
    queue->rear= NULL;
       
}

//--------------------Enqueue----------------------

void enqueue(ReadyQueue* queue, PCB* pcb){

    if(queue->rear == NULL){
        queue->front = queue->rear = pcb;
    }
    else{
        queue->rear->next= pcb;
        queue->rear = pcb;
    }
    printf("take input %d enqueue to implement in queue. \n",pcb->process_id);


}

PCB* dequeue(ReadyQueue* queue){
    if(queue->front == NULL){
        printf("Ready queue is empty. \n");
        return NULL;
    }

    PCB* temp = queue->front;
    queue->front = queue->front->next;

    if(queue->front == NULL){
        queue->rear = NULL;
    }
    printf("process %d dequeued from ready queue . \n",temp->process_id);
    return temp;
}


//--------------------------fuction to display queue---------------

void displayQueue(ReadyQueue* queue){
    if(queue->front == NULL){
        printf("Ready queue is empty. \n");
        return;
    }
    PCB* temp = queue->front;
    printf("Ready Queue: \n");
    while(temp != NULL){
        printf("Process ID: %d, Priority: %d , State: %s\n",temp->process_id,temp ->priority, temp->state);
        temp = temp->next;
    }
}

int main(){
    ReadyQueue queue;
    initReadyQueue(&queue);
    int n;
    printf("Enter the number of processes :");
    scanf("%d",&n);

    for(int i=0; i<n; i++){
        int process_id,priority;
        char state[20];

        printf("Enter details for process %d\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &process_id);
        printf("Priority: ");
        scanf("%d", &priority);
        printf("State: ");
        scanf("%s", state);

        PCB* pcb = createPCB(process_id,priority,state);
        enqueue(&queue,pcb);
    }

    displayQueue(&queue);

    dequeue(&queue);
    dequeue(&queue);

    displayQueue(&queue);

    return 0;
}