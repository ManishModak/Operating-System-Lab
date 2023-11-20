#include<stdio.h>
#include<stdbool.h>

int main() {
    int processes, resources;

    printf("Enter The No of Processes: ");
    scanf("%d", &processes);

    printf("\nEnter The No Resources: ");
    scanf("%d", &resources);

    int allocation[processes][resources], max[processes][resources], available[resources];

    for (int i = 0; i < processes; i++) {
        printf("Enter %dth process allocation: ", i);

        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    for (int i = 0; i < processes; i++) {
        printf("Enter %dth process max: ", i);

        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources: ");
    for (int j = 0; j < resources; j++) {
        scanf("%d", &available[j]);
    }

    int need[processes][resources];

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int safeSeq[processes], safeSeqIndex = 0;

    bool inSafeSeq[processes];
    for (int i = 0; i < processes; i++) {
        inSafeSeq[i] = false;
    }

    bool safeSeqAchieved = false;

    for (int count = 0; count < processes; count++) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!inSafeSeq[i]) {
                bool checkCondition = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > available[j]) {
                        checkCondition = false;
                        break;
                    }
                }
                if (checkCondition) {
                    for (int k = 0; k < resources; k++) {
                        available[k] += allocation[i][k];
                    }
                    safeSeq[safeSeqIndex++] = i;
                    inSafeSeq[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break; // Break if no safe sequence is possible
        }
        if (safeSeqIndex == processes) {
            safeSeqAchieved = true;
            break;
        }
    }

    if (safeSeqAchieved) {
        printf("Following is the Safe Sequence: ");
        for (int k = 0; k < processes - 1; k++) {
            printf("P%d -> ", safeSeq[k]);
        }
        printf("P%d\n", safeSeq[processes - 1]);
    } else {
        printf("Safe Sequence not met\n");
    }

    return 0;
}
