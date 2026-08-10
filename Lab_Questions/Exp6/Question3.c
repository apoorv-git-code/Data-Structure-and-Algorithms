#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct {
    char pid[5];
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

// Global Circular Queue for Process Pointers/Indices
int queue[MAX];
int front = -1, rear = -1;

void enqueue(int index) {
    if ((rear + 1) % MAX == front) return;
    if (front == -1) front = 0;
    rear = (rear + 1) % MAX;
    queue[rear] = index;
}

int dequeue() {
    if (front == -1) return -1;
    int index = queue[front];
    if (front == rear) front = rear = -1;
    else front = (front + 1) % MAX;
    return index;
}

int main() {
    int n, tq, currentTime = 0, completed = 0;
    Process p[MAX];
    char executionOrder[100][5];
    int execCount = 0;
    char completionOrder[MAX][5];
    int compCount = 0;

    printf("Enter No. of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter PID and Burst Time for P%d: ", i + 1);
        scanf("%s %d", p[i].pid, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        enqueue(i); // Initial insertion into circular queue
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Simulation Loop
    while (completed < n) {
        int i = dequeue();
        
        // Record Execution Order
        strcpy(executionOrder[execCount++], p[i].pid);

        if (p[i].remainingTime > tq) {
            currentTime += tq;
            p[i].remainingTime -= tq;
            enqueue(i); // Move to rear
        } else {
            currentTime += p[i].remainingTime;
            p[i].remainingTime = 0;
            p[i].completionTime = currentTime;
            p[i].turnaroundTime = p[i].completionTime; // Arrival is 0
            p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
            
            // Record Completion Order
            strcpy(completionOrder[compCount++], p[i].pid);
            completed++;
        }
    }

    // --- DISPLAY RESULTS ---
    printf("\nOrder of execution: ");
    for (int i = 0; i < execCount; i++) {
        printf("%s%s", executionOrder[i], (i == execCount - 1) ? "" : " -> ");
    }

    printf("\nOrder of completion: ");
    for (int i = 0; i < compCount; i++) {
        printf("%s%s", completionOrder[i], (i == compCount - 1) ? "" : " -> ");
    }

    printf("\n\n%-10s %-15s %-15s %-15s %-15s\n", "PID", "Burst Time", "Comp. Time", "TAT", "Wait Time");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-15d %-15d %-15d %-15d\n", 
               p[i].pid, p[i].burstTime, p[i].completionTime, 
               p[i].turnaroundTime, p[i].waitingTime);
    }

    return 0;
}