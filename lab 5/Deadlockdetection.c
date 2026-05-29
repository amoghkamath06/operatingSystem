#include <stdio.h>

#define MAX 10

int main() {
    int n, m;

    int allocation[MAX][MAX], request[MAX][MAX], available[MAX];
    int work[MAX], finish[MAX];
    int i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }


    for(j = 0; j < m; j++) {
        work[j] = available[j];
    }

    for(i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int found;
    do {
        found = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int canExecute = 1;

                for(j = 0; j < m; j++) {
                    if(request[i][j] > work[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if(canExecute) {

                    for(k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
    } while(found);


    int deadlock = 0;
    printf("\nDeadlocked Processes: ");
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
        printf("No Deadlock\n");
    else
        printf("\nSystem is in Deadlock!\n");

    return 0;
}
