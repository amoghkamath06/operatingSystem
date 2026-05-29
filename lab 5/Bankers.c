#include <stdio.h>
#include <stdbool.h>

bool safetyAlgorithm(int n, int m, int allocation[n][m], int need[n][m], int available[m]) {
    int work[m];
    bool finish[n];
    int safeSeq[n];


    for (int i = 0; i < m; i++)
        work[i] = available[i];

    for (int i = 0; i < n; i++)
        finish[i] = false;

    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if (i != n - 1) printf(" -> ");
    }
    printf("\n");
    return true;
}


void resourceRequest(int n, int m, int allocation[n][m], int need[n][m], int available[m]) {
    int process;
    printf("\nEnter process number making request (0-%d): ", n - 1);
    scanf("%d", &process);

    int request[m];
    printf("Enter request vector:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);


    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            printf("\nError: Process has exceeded its maximum claim.\n");
            return;
        }
    }

    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            printf("\nResources not available. Process must wait.\n");
            return;
        }
    }


    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (safetyAlgorithm(n, m, allocation, need, available)) {
        printf("\nRequest can be granted safely.\n");
    } else {
        printf("\nRequest cannot be granted (unsafe).\n");

        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m];
    int available[m];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Maximum Demand Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);


    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];


    if (!safetyAlgorithm(n, m, allocation, need, available)) {
        printf("\nSystem is in an UNSAFE state initially.\n");
        return 0;
    }


    resourceRequest(n, m, allocation, need, available);

    return 0;
}
