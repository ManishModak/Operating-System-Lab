#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
};


void roundRobin() {
    int n, quantum;

    printf("\nEnter No. of Processes: ");
    scanf("%d", &n);

    struct Process data[n];

    for (int i = 0; i < n; i++) {
        data[i].pid = i;

        printf("\nEnter Arrival Time of %dth Process: ", i);
        scanf("%d", &data[i].arrivalTime);

        printf("Enter Burst Time of %dth Process: ", i);
        scanf("%d", &data[i].burstTime);
    }

    printf("\nEnter Quantum Time: ");
    scanf("%d", &quantum);

    int remaining_time[n];
    int total_turnaround_time = 0, total_waiting_time = 0;

    for (int i = 0; i < n; i++)
        remaining_time[i] = data[i].burstTime;

    printf("\nGantt Chart\n");
    int completed = 0;
    int time = 0;

    while (completed < n) {
        int flag = 0;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                flag = 1;

                if (remaining_time[i] > quantum) {
                    printf("| P%d ", i);
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    printf("| P%d ", i);
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    total_waiting_time += time - data[i].arrivalTime - data[i].burstTime;
                    total_turnaround_time += time - data[i].arrivalTime;
                    completed++;
                }
            }
        }

        if (flag == 0)
            break;
    }

    printf("|");

    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_waiting_time = (float)total_waiting_time / n;

    printf("\nAverage Turn Around Time: %.3f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.3f\n", avg_waiting_time);
}


void shortestJobFirst() {
    int n;

    printf("\nEnter No. of Processes: ");
    scanf("%d", &n);

    struct Process data[n];

    for (int i = 0; i < n; i++) {
        data[i].pid = i;

        printf("\nEnter Arrival Time of %dth Process: ", i);
        scanf("%d", &data[i].arrivalTime);

        printf("Enter Burst Time of %dth Process: ", i);
        scanf("%d", &data[i].burstTime);
    }

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j].arrivalTime > data[j + 1].arrivalTime) {
                struct Process temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    int completed = 0;
    int time = data[0].arrivalTime;
    int shortest = 0; // Index of the process with the shortest burst time
    int remaining[n];
    int total_turnaround_time = 0, total_waiting_time = 0;
    
    for (int i = 0; i < n; i++)
        remaining[i] = data[i].burstTime;

    printf("\nGantt Chart\n");

    while (completed != n) {
        int minBurst = INT_MAX;
        int selectedProcess = -1;

        for (int i = 0; i < n; i++) {
            if (data[i].arrivalTime <= time && remaining[i] < minBurst && remaining[i] > 0) {
                minBurst = remaining[i];
                selectedProcess = i;
            }
        }

        if (selectedProcess == -1) {
            time++;
            continue;
        }

        remaining[selectedProcess]--;
        time++;

        printf("| P%d ", data[selectedProcess].pid);

        if (remaining[selectedProcess] == 0) {
            completed++;
            total_turnaround_time += time - data[selectedProcess].arrivalTime;
            total_waiting_time += time - data[selectedProcess].arrivalTime - data[selectedProcess].burstTime;
        }
    }

    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_waiting_time = (float)total_waiting_time / n;

    printf("\nAverage Turn Around Time: %.3f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.3f\n", avg_waiting_time);
}

int main() {
    int choice;

    do {
        printf("\n1. Round Robin\n");
        printf("2. Shortest Job First\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                roundRobin();
                break;
            case 2:
                shortestJobFirst();
                break;
            case 3:
                printf("\nProgram Exited\n");
                break;
            default:
                printf("\nInvalid Choice\n");
        }

    } while (choice != 3);

    return 0;
}

