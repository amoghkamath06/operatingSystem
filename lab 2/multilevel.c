#include <stdio.h>

#define MAX 100

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[MAX], at[MAX], bt[MAX], rt[MAX], type[MAX];
    int ct[MAX], tat[MAX], wt[MAX];

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        pid[i] = i;

        printf("Enter arrival time: ");
        scanf("%d", &at[i]);

        printf("Enter burst time: ");
        scanf("%d", &bt[i]);

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &type[i]);

        rt[i] = bt[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int temp;

                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = rt[i]; rt[i] = rt[j]; rt[j] = temp;
                temp = type[i]; type[i] = type[j]; type[j] = temp;
            }
        }
    }

    int sysQ[MAX], userQ[MAX];
    int sf = -1, sr = -1;
    int uf = -1, ur = -1;

    int time = 0, completed = 0, i = 0;
    int current = -1;

    while (completed < n) {

        while (i < n && at[i] <= time) {
            if (type[i] == 0) {
                if (sf == -1) sf = 0;
                sysQ[++sr] = i;
            } else {
                if (uf == -1) uf = 0;
                userQ[++ur] = i;
            }
            i++;
        }

        if (current != -1) {
            if (type[current] == 1 && sf != -1) {
                userQ[++ur] = current;
                current = -1;
            }
        }

        if (current == -1) {
            if (sf != -1) {
                current = sysQ[sf];
                if (sf == sr) sf = sr = -1;
                else sf++;
            } else if (uf != -1) {
                current = userQ[uf];
                if (uf == ur) uf = ur = -1;
                else uf++;
            } else {
                time++;
                continue;
            }
        }

        rt[current]--;
        time++;

        if (rt[current] == 0) {
            ct[current] = time;
            completed++;
            current = -1;
        }
    }

    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               pid[i],
               (type[i] == 0) ? "System" : "User",
               at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
