#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    int jobID;
    char userName[50];
    int numPages;
    int priority;
    int arrivalOrder; // To maintain FIFO for same priorities
} PrintJob;

PrintJob queue[MAX];
int jobCount = 0;
int totalArrivals = 0;

// Function to insert a job into the Priority Queue
void insertJob(int id, char name[], int pages, int prio) {
    if (jobCount >= MAX) {
        printf("Queue Full! Cannot add Job %d\n", id);
        return;
    }

    PrintJob newJob;
    newJob.jobID = id;
    strcpy(newJob.userName, name);
    newJob.numPages = pages;
    newJob.priority = prio;
    newJob.arrivalOrder = totalArrivals++;

    // Find the correct position to maintain descending order
    // If priorities are equal, the new job goes after existing ones (FIFO)
    int i = jobCount - 1;
    while (i >= 0 && (queue[i].priority < newJob.priority)) {
        queue[i + 1] = queue[i];
        i--;
    }
    
    queue[i + 1] = newJob;
    jobCount++;
    printf("Job %d added to queue.\n", id);
}

// Function to process (delete) the highest priority job
void processJobs() {
    if (jobCount == 0) {
        printf("\nNo jobs to process.\n");
        return;
    }

    printf("\n--- Processing Print Jobs ---\n");
    printf("%-10s %-15s %-10s %-10s\n", "Job ID", "User", "Pages", "Priority");
    
    // In this array implementation, the highest priority is always at index 0
    for (int i = 0; i < jobCount; i++) {
        printf("%-10d %-15s %-10d %-10d\n", 
               queue[i].jobID, 
               queue[i].userName, 
               queue[i].numPages, 
               queue[i].priority);
    }
    jobCount = 0; // All jobs processed
}

int main() {
    // Simulating Job Submissions
    insertJob(101, "Apoorv", 5, 3);
    insertJob(102, "Bhoovi", 12, 8);
    insertJob(103, "Jiya", 2, 8); 
    insertJob(104, "Hardik", 1, 10);  // Highest priority
    insertJob(105, "Mridul", 7, 1);     // Lowest priority

    processJobs();

    return 0;
}