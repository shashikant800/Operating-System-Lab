#include <stdio.h>
#include <stdlib.h>
struct Process{
int pid;
int arrivalTime;
int burstTime;
int remainingTime;
int completionTime;
};
void findRobin(struct Process *proc, int n, int timeQ){
int currentTime =0;
int completed = 0, i=0;
int totalWaitingTime = 0, totalTurnAroundTime = 0;
int *waitQueue = (int *)malloc(n * sizeof(int));
for (int i = 0; i < n; i++)
{
proc[i].remainingTime = proc[i].burstTime;
waitQueue[i] = 0;
}
while (completed!=n)
{
int executed = 0;
for (int i = 0; i < n; i++)
{
if (proc[i].arrivalTime<= currentTime && proc[i].remainingTime>0)
{
executed =1;
if (proc[i].remainingTime <= timeQ)
{
currentTime = currentTime + proc[i].remainingTime;
proc[i].completionTime = currentTime;
proc[i].remainingTime = 0;
completed++;
int turnAroundTime = proc[i].completionTime -
proc[i].arrivalTime;
int waitingTime = turnAroundTime - proc[i].burstTime;
totalTurnAroundTime = totalTurnAroundTime +
turnAroundTime;
totalWaitingTime = totalWaitingTime + waitingTime;
}
else{
currentTime = currentTime + timeQ;
proc[i].remainingTime = proc[i].remainingTime - timeQ;
}
}
}
if (executed ==0)
{
currentTime++;
}
}
printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
for (int i = 0; i < n; i++) {
int turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
int waitingTime = turnaroundTime - proc[i].burstTime;
printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n"
, proc[i].pid,
proc[i].arrivalTime, proc[i].burstTime, proc[i].completionTime,
turnaroundTime, waitingTime);
}
printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);
printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
free(waitQueue);
}
int main() {
int n, timeQuantum;
struct Process *proc;
printf("Enter number of processes: ");
scanf("%d"
, &n);
proc = (struct Process *)malloc(n * sizeof(struct Process));
if (proc == NULL) {
printf("Memory allocation failed\n");
return 1;
}
for (int i = 0; i < n; i++) {
proc[i].pid = i + 1;
printf("Enter arrival time and burst time for process %d: ",
proc[i].pid);
scanf("%d %d"
, &proc[i].arrivalTime, &proc[i].burstTime);
}
printf("Enter time quantum: ");
scanf("%d"
, &timeQuantum);
findRobin(proc, n, timeQuantum);
free(proc);
return 0;
}