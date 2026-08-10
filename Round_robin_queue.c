#include <stdio.h>
#include<stdbool.h>

void calculateRoundRobin(int processes[], int n, int bt[], int quantum) {
    int rem_bt[n]; // Array to store remaining burst times
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0; // Current time

    printf("\nExecution Sequence:\n");
    while (1) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false; // There is still a pending process

                if (rem_bt[i] > quantum) {
                    t = t + quantum;
                    rem_bt[i] = rem_bt[i] - quantum;
                    printf("P%d runs for %d units (Remaining: %d)\n", i + 1, quantum, rem_bt[i]);
                } else {
                    // This is the last cycle for this process
                    t = t + rem_bt[i];
                    printf("P%d runs for %d units and FINISHES at time %d\n", i + 1, rem_bt[i], t);
                    printf("\nCycle completed %d!\n ");
                    rem_bt[i] = 0;
                }
            }
        }

        if (done == true)
        break;

    }
}

int main() {
    int processes[] = {1, 2, 3, 4};
    int n = sizeof(processes) / sizeof(processes[0]);
    int bt[] = {5, 4, 2, 7}; // Time required for each process
    int quantum = 2;               // Time Quantum

    printf("PID | Burst Time\n");
    for(int i = 0; i < n; i++) printf("P%d  |  %d\n", i+1, bt[i]);

    calculateRoundRobin(processes, n, bt, quantum);

    return 0;
}

















// #include <stdio.h>
// #include <string.h>

// #define SIZE 5
// #define QUANTUM 2 // Time slice for each student's "turn"

// struct Student {
//     int sap_id;
//     char name[50];
//     int burst_time;     // Total time required
//     int remaining_time; // Time left to complete
// };

// struct Student queue[SIZE];
// int front = -1, rear = -1;

// // Function to add a student to the queue
// void enqueue(struct Student s) {
//     if ((rear + 1) % SIZE == front) {
//         printf("Queue Full! Cannot add %s\n", s.name);
//     } else {
//         if (front == -1) front = 0;
//         rear = (rear + 1) % SIZE;
//         queue[rear] = s;
//     }
// }

// // Function to remove a student from the queue
// struct Student dequeue() {
//     struct Student s = queue[front];
//     if (front == rear) {
//         front = rear = -1;
//     } else {
//         front = (front + 1) % SIZE;
//     }
//     return s;
// }

// void roundRobin() {
//     if (front == -1) {
//         printf("\nNo students in the queue to process.\n");
//         return;
//     }

//     printf("\n--- Starting Round Robin Scheduling (Quantum: %d) ---\n", QUANTUM);

//     while (front != -1) {
//         struct Student current = dequeue();
        
//         printf("\nProcessing Student: %s (SAP: %d)\n", current.name, current.sap_id);
//         printf("  Remaining Time before: %d\n", current.remaining_time);

//         if (current.remaining_time > QUANTUM) {
//             // Student needs more time than the quantum
//             current.remaining_time -= QUANTUM;
//             printf("  Turn finished. Remaining Time: %d. Moving to back of queue.\n", current.remaining_time);
//             enqueue(current);
//         } else {
//             // Student finishes within or exactly at the quantum
//             printf("  Student %s has completed their task!\n", current.name);
//             current.remaining_time = 0;
//         }
//     }
//     printf("\n--- All processes completed ---\n");
// }

// int main() {
//     int n, i;
//     printf("Enter number of students (max %d): ", SIZE);
//     scanf("%d", &n);

//     for (i = 0; i < n; i++) {
//         struct Student temp;
//         printf("\nDetails for Student %d:\n", i + 1);
//         printf("SAP ID: "); scanf("%d", &temp.sap_id);
//         printf("Name: "); scanf("%s", temp.name);
//         printf("Burst Time (Task Duration): "); scanf("%d", &temp.burst_time);
//         temp.remaining_time = temp.burst_time;
        
//         enqueue(temp);
//     }

//     roundRobin();

//     return 0;
// }