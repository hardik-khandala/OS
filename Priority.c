#include <stdio.h>

struct process
{
    int pid, btime, wtime, ttime, atime, ptime, priority;
} p[10], temp;

int main()
{
    int i, j, k, n, ttur, twat, put;
    float awat, atur, thpt;

    printf("Enter no. of process: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Arrival time for process P%d (in ms) : ", (i + 1));
        scanf("%d", &p[i].atime);
        p[i].pid = i + 1;
    }
    for (i = 0; i < n; i++)
    {
        printf("Burst time for process P%d (in ms) : ", (i + 1));
        scanf("%d", &p[i].btime);
        p[i].pid = i + 1;
    }
    for (i = 0; i < n; i++)
    {
        printf("Priority for process P%d (in ms) : ", (i + 1));
        scanf("%d", &p[i].priority);
        p[i].pid = i + 1;
    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if ((p[i].priority > p[j].priority) || (p[i].priority == p[j].priority && p[i].pid > p[j].pid))
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].ptime = 0;
    for (i = 0; i < (n + 1); i++)
    {
        p[i + 1].ptime = p[i].ptime + p[i].btime;
    }

    p[0].wtime = 0;
    p[0].ttime = 0;
    for (i = 0; i < n; i++)
    {
        p[i + 1].ttime = p[i + 1].ptime - p[i].atime;
        p[i + 1].wtime = p[i + 1].ttime - p[i].btime;
    }

    ttur = twat = 0;
    for (i = 0; i < n + 1; i++)
    {
        ttur += p[i + 1].ttime;
        twat += p[i + 1].wtime;
    }
    awat = (float)twat / n;
    atur = (float)ttur / n;
    thpt = (float)n / p[n].ptime;
    put = (p[n].ptime / (p[n].ptime + 0)) * 100;

    printf("\n\nGANTT Chart\n");
    for (i = 0; i < (7 * n); i++)
    {
        printf("-");
    }
    printf("\n| ");
    for (i = 0; i < n; i++)
    {
        printf("P%d", p[i].pid);
        printf("  |  ");
    }
    printf("\n");
    for (i = 0; i < (7 * n); i++)
    {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < 2; i++)
    {
        printf("%d", p[i].ptime);
        printf("     ");
    }
    for (i = 2; i < 4; i++)
    {
        printf("%d", p[i].ptime);
        printf("     ");
    }
    for (i = 4; i < (n + 1); i++)
    {
        printf("%d", p[i].ptime);
        printf("     ");
    }
    printf("\n\n        Priority Process Scheduling Table\n");
    for (i = 0; i < 65; i++)
        printf("-");
    printf("\n| Time |  Process  |  Priority | Turnaround Time | Waiting Time | \n");
    printf("|      | Completed |           |    =(P.C-P.S)   |   =(T.T-B.T) | \n");
    for (i = 0; i < 65; i++)
        printf("-");
    printf("\n|   0  |     -\t   |     -     |        -        |      -       |");
    for (i = 0; i < n; i++)
        printf("\n|%4d  |     P%-2d   |%6d     |%9d        |%7d       |", p[i + 1].ptime, p[i].pid, p[i].priority, p[i + 1].ttime, p[i + 1].wtime);
    printf("\n");
    for (i = 0; i < 65; i++)
        printf("-");

    printf("\n\nAverage turn around time = Total Turn Around Time / No. of processes \n=");
    for (i = 1; i < n; i++)
    {
        printf(" TT(P%d) +", i);
    }
    printf(" TT(P%d) / %d \n= ", n, n);
    for (i = 1; i < n; i++)
    {
        printf("%d+", p[i].ttime);
    }
    printf("%d/%d \n= %d/%d \n= %.2f ms\n\n", p[n].ttime, n, ttur, n, atur);
    printf("Average waiting time = Total Waiting Time / No. of processes \n=");
    for (i = 1; i < n; i++)
    {
        printf(" WT(P%d) +", i);
    }
    printf(" WT(P%d) / %d \n= ", n, n);
    for (i = 1; i < n; i++)
    {
        printf("%d+", p[i].wtime);
    }
    printf("%d3/%d \n= %d/%d \n= %.2f ms\n\n", p[n].wtime, n, twat, n, awat);

    printf("Throughtput \n= (No. of Process Completed / Total Time) \n= %d / %d \n= %.2f ms\n\n", n, p[n].ptime, thpt);
    printf("Processor Utilisation \n= (Processor Busy Time / (Processor Busy Time + Processor Ideal Time)) * 100 \n= (%d / (%d + 0)) * 100 \n= (1 / 1) * 100 \n= %d%%", p[n].ptime, p[n].ptime, put);
    return 0;
}
