
#include <stdio.h>

int main() {
    int n, i, time = 0, remain, tq;
    int at[20], bt[20], rt[20], ct[20], tat[20], wt[20];

    float total_tat = 0, total_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rt[i] = bt[i];  // remaining time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    remain = n;

    while(remain > 0) {
        int executed = 0;

        for(i = 0; i < n; i++) {

            if(rt[i] > 0 && at[i] <= time) {

                executed = 1;

                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                }
                else {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    remain--;
                }
            }
        }

        // If no process is executed, move time forward
        if(executed == 0) {
            time++;
        }
    }

    // Calculate TAT and WT
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);

    return 0;
}
