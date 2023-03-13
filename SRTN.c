#include <stdio.h>
#include <stdlib.h>
#define MAX_PROCESS 100

struct Process
{
    int pid;
    int bTime;
    int aTime;
    int rTime;
    int cTime;
    int wTime;
    int tTime;
} p[MAX_PROCESS],temp;

int main()
{
    int n, time, current_time = 0, completed = 0, i, j, twat, ttur,put;
    float awat, atur;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Arrival time for process P%d (in ms) : ", (i + 1));
        scanf("%d", &p[i].aTime);
        p[i].pid = i + 1;
    }

    for (i = 0; i < n; i++)
    {
        printf("Burst time for process P%d (in ms) : ", (i + 1));
        scanf("%d", &p[i].bTime);
        p[i].pid = i + 1;
        p[i].rTime = p[i].bTime;
    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if ((p[i].aTime > p[j].aTime) || (p[i].aTime == p[j].aTime && p[i].pid > p[j].pid))
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
   // printf("\nExecution order: ");
    while (completed < n)
    {
        int min_remaining_time = -1, index = -1;
        for (i = 0; i < n; i++)
        {
            if (p[i].aTime <= current_time && p[i].rTime > 0)
            {
                if (min_remaining_time == -1 || p[i].rTime < min_remaining_time)
                {
                    min_remaining_time = p[i].rTime;
                    index = i;
                }
            }
        }
        if (index == -1)
        {
            current_time++;
            continue;
        }
        p[index].rTime--;
        current_time++;
        if (p[index].rTime == 0)
        {
           // printf("P%d ", p[index].pid);
            p[index].cTime = current_time;
            p[index].tTime = p[index].cTime - p[index].aTime;
            p[index].wTime = p[index].tTime - p[index].bTime;
            completed++;
        }
    }

    printf("\n\nGantt Chart\n");
    for (i = 0; i < (5.2 * n); i++)
    {
        printf("-");
    }
    printf("\n| ");
    for (i = 0; i < n; i++)
    {
        printf("P%d", p[i].pid);
        printf(" | ");
    }
    printf("\n");
    for (i = 0; i < (5.2 * n); i++)
    {
        printf("-");
    }
    printf("\n");
    printf("0   ");
    for (i = 0; i < n; i++)
    {
        printf("%d", p[i].cTime);
        if (p[i+1].cTime >= 10)
        {
            printf("   ");
        }
        else if (p[i+1].cTime < 10)
        {
            printf("     ");
        }
    }

    printf("\n");
    printf("\n\n         SRTN Process Scheduling Table\n");
    for (i = 0; i < 56; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("| Time  |  Process  | Turnaround Time  | Waiting Time  |\n");
    printf("|       | Completed |    (P.C-P.S)     |  (T.T-B.T)    |\n");
    for (i = 0; i < 56; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("|    0   |     -    |        -         |       -       |\n");
    for (i = 0; i < n; i++)
    {
        printf("|  %3d   |    P%d    |      %3d         |     %3d       |\n", p[i].cTime, p[i].pid, p[i].tTime, p[i].wTime);
    }
    for (i = 0; i < 56; i++)
    {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < n; i++)
    {
        p[i].tTime = p[i].cTime - p[i].aTime;
        p[i].wTime = p[i].tTime - p[i].bTime;
    }
    ttur = twat = 0;
    for (i = 0; i < (n + 1); i++)
    {
        ttur += p[i].tTime;
        twat += p[i].wTime;
    }
    awat = (float)twat / n;
    atur = (float)ttur / n;
    printf("\n\nAverage turn around time = (Total Turn Around Time / No. of processes)\n= ");
    for (i = 1; i < n; i++)
    {
        printf("TT(P%d)+", i);
    }
    printf("TT(P%d)/%d \n= (", n, n);
    for (i = 1; i < (n - 1); i++)
    {
        printf("%d+", p[i].tTime);
    }
    printf("%d)/%d \n= %d/%d \n= %.2f ms\n\n", p[n - 1].tTime, n, ttur, n, atur);

    printf("Average waiting time = (Total Waiting Time / No. of processes)\n= ");
    for (i = 1; i < n; i++)
    {
        printf("WT(P%d)+", i);
    }
    printf("WT(P%d))/%d = (", n, n);
    for (i = 0; i < (n - 1); i++)
    {
        printf("%d+", p[i].wTime);
    }
    printf("%d)/%d \n= %d/%d \n= %.2f ms\n\n", p[n - 1].wTime, n, twat, n, awat);



    int max = p[0].cTime;
    for (i = 0; i < n; i++)
    {
        if (p[i].cTime > max)
            max = p[i].cTime;
    }
    float throughput = (float)n / max;
    printf("Throughtput = (No. of Process Completed / Total Time) \n= %d / %d \n= %.2fms\n\n", n, max, throughput);
    put = ( max / (max + 0))*100;
    printf("Processor Utilisation = (Processor Busy Time / (Processor Busy Time + Processor Ideal Time)) \n= (%d / (%d + 0))*100 \n= (1 / 1)*100 \n= %d%%",max,max,put);
    return 0;
}
