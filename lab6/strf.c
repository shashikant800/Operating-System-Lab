#include <stdio.h>
#include <stdlib.h>
struct Process{
int pid;
int arrivalTime;
int burstTime;
int remainingTime;
int completionTime;
};
void findSRTF(struct Process *proc, int n){
int completed = 0, currentTime = 0, minIndex = -1;
int minRemaining = 9999;
int totalWaiting = 0, totalTurnAroundTime = 0;
int isProcessRunning=0;
while (completed!=n)
{
for (int i = 0; i < n; i++)
{
if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime >
0 && proc[i].remainingTime<minRemaining)
{
minRemaining = proc[i].remainingTime;
minIndex = i;
isProcessRunning = 1;
}
}
if (minIndex == -1)
{
currentTime++;
continue;
}
proc[minIndex].remainingTime--;
currentTime++;
if (proc[minIndex].remainingTime ==0)
{
completed++;
proc[minIndex].completionTime = currentTime;
int turnAroundTime = proc[minIndex].completionTime -
proc[minIndex].arrivalTime;
int waitingTime = turnAroundTime - proc[minIndex].burstTime;
totalWaiting = totalWaiting + waitingTime;
totalTurnAroundTime = totalTurnAroundTime + turnAroundTime;
minRemaining = 9999;
minIndex = -1;
isProcessRunning = 0;
}
if (!isProcessRunning) {
minRemaining = 9999;
}
}
printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
for (int i = 0; i < n; i++)
{
int turnAroundTime = proc[i].completionTime - proc[i].arrivalTime;
int waitingTime = turnAroundTime - proc[i].burstTime;
printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n"
, proc[i].pid,
proc[i].arrivalTime, proc[i].burstTime, proc[i].completionTime,
turnAroundTime, waitingTime);
}
printf("Average turnaround time: %.2f\n", (float)totalTurnAroundTime/n);
printf("Average waiting time: %.2f\n", (float)totalWaiting/n);
}
int main(){
int n;
struct Process *proc;
printf("Enter number of processes: ");
scanf("%d"
, &n);
proc = (struct Process *)malloc(sizeof(struct Process));
if (proc==NULL)
{
printf("Memory allocation failed\n");
return 1;
}
for(int i = 0; i<n; i++){
proc[i].pid = i+1;
printf("Enter arrival time and burst time for process %d: ",
proc[i].pid);
scanf("%d %d"
, &proc[i].arrivalTime, &proc[i].burstTime);
proc[i].remainingTime = proc[i].burstTime;
}
findSRTF(proc, n);
free(proc);
return 0;
}