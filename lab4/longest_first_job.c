#include <stdio.h>

struct Process {
    int pid;       // PID
    int burstTime; // B t
    int waitTime;  // w t
    int turnAroundTime; // TT
};

void findWaitingTime(struct Process proc[], int n) {
    proc[0].waitTime = 0; // Waiting time for the first process is 0
    
    for (int i = 1; i < n; i++) {
        proc[i].waitTime = proc[i-1].waitTime + proc[i-1].burstTime;
    }
}

void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnAroundTime = proc[i].burstTime + proc[i].waitTime;
    }
}

void findAverageTimes(struct Process proc[], int n) {
    findWaitingTime(proc, n);
    findTurnAroundTime(proc, n);
    
    int totalWaitTime = 0, totalTurnAroundTime = 0;
    
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    for (int i = 0; i < n; i++) {
        totalWaitTime += proc[i].waitTime;
        totalTurnAroundTime += proc[i].turnAroundTime;
        
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime, proc[i].waitTime, proc[i].turnAroundTime);
    }
    
    printf("Average Waiting Time: %.2f\n", (float)totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);
}

void sortByBurstTime(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].burstTime < proc[j + 1].burstTime) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
    }
    
    // Sort processes by burst time (SJF)
    sortByBurstTime(proc, n);
    
    // Find and display average waiting time and turnaround time
    findAverageTimes(proc, n);
    
    return 0;
}