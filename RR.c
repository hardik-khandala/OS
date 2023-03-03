#include <stdio.h>

void main()
{
    int i, x = -1, k[10], m = 0, n, t, s = 0;
    int a[50], temp, b[50], p[10], bur[10], bur1[10];
    int wtime[10], ttime[10], ctime[10], atime[10], ttur = 0, twat = 0, j = 0, put, tottime = 0, towtime = 0;
    float attime, awtime, thpt;

    printf("Enter no. of process : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("arrival time for process P%d: ", (i + 1));
        scanf("%d", &atime[i]);
        atime[i] = atime[i];
    }
    for (i = 0; i < n; i++)
    {
        printf("Burst time for process P%d: ", (i + 1));
        scanf("%d", &bur[i]);
        bur1[i] = bur[i];
    }
    printf("Enter the Quantum Time (in ms): ");
    scanf("%d", &t);

    for (i = 0; i < n; i++)
    {
        b[i] = bur[i] / t;
        if ((bur[i] % t) != 0)
            b[i] += 1;
        m += b[i];
    }

    printf("\nGANTT Chart\n");
    for (i = 0; i < m; i++)
        printf("--------");
    printf("\n");

    a[0] = 0;
    while (j < m)
    {
        if (x == n - 1)
            x = 0;
        else
            x++;
        if (bur[x] >= t)
        {
            bur[x] -= t;
            a[j + 1] = a[j] + t;

            if (b[x] == 1)
            {
                p[s] = x;
                k[s] = a[j + 1];
                s++;
            }
            j++;
            b[x] -= 1;
            printf("  P%d    |", x + 1);
        }
        else if (bur[x] != 0)
        {
            a[j + 1] = a[j] + bur[x];
            bur[x] = 0;
            if (b[x] == 1)
            {
                p[s] = x;
                k[s] = a[j + 1];
                s++;
            }
            j++;
            b[x] -= 1;
            printf("  P%d  |", x + 1);
        }
    }

    printf("\n");
    for (i = 0; i < m; i++)
        printf("--------");
    printf("\n");

    for (j = 0; j <= m; j++)
        printf("%d\t", a[j]);

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i] > p[j])
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;

                temp = k[i];
                k[i] = k[j];
                k[j] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        wtime[i] = k[i] - bur1[i];
        ctime[i] = k[i];
        ttime[i] = ctime[i] - atime[i];
        attime = attime + ttime[i];
        awtime = awtime + wtime[i];
        t = ctime[n - 1];
    }
    for (i = 2; i < n + 1; i++)
    {
        towtime += wtime[i - 1];
        tottime += ttime[i - 1];
    }

    printf("\n\n           Round Robin Process Table\n");
    for (i = 0; i < 60; i++)
        printf("-");
    printf("\n|  Time  |    Process    | Turnaround Time  | Waiting Time | \n");
    printf("|        |   Completed   |    =(P.C-P.S)    |  =(T.T-B.T)  | \n");
    for (i = 1; i < 61; i++)
        printf("-");
    printf("\n|    0   |       -       |        -         |       -      |", ctime[i]);
    for (i = 0; i < n; i++)
        printf("\n|  %3d   |       P%-2d     |%9d         |%8d      |", ctime[i], p[i] + 1, ttime[i], wtime[i]);
    printf("\n");
    for (i = 0; i < 60; i++)
        printf("-");

    printf("\n\nAverage turn around time = Total Turn Around Time / No. of processes \n=");
    for (i = 1; i < n; i++)
    {
        printf(" TT(P%d) +", i);
    }
    printf(" TT(P%d)/%d \n= (", n, n);
    for (i = 0; i < (n - 1); i++)
    {
        printf("%d+", ttime[i]);
    }
    attime = (float)tottime / n;
    printf("%d)/%d \n= ", ttime[n - 1], n);
    printf("%d/%d \n=", tottime, n);
    printf(" %.2f ms", attime);
    printf("\n\nAverage waiting time = Total Waiting Time / No. of processes \n=");
    for (i = 1; i < n; i++)
    {
        printf(" WT(P%d) + ", i);
    }
    printf("WT(P%d)/%d \n= (", n, n);
    for (i = 0; i < (n - 1); i++)
    {
        printf("%d+", wtime[i]);
    }
    awtime = (float)towtime / n;
    printf("%d)/%d \n= ", wtime[n - 1], n);
    printf("%d/%d \n=", towtime, n);
    printf(" %.2f ms", awtime);

    printf("\n\nThroughtput = (No. of Process Completed / Total Time) \n= %d / %d \n=%5.2f ms\n\n", n, t, (float)n / (float)t);
    put = (ctime[i - 1] / (ctime[i - 1] + 0)) * 100;
    printf("Processor Utilisation \n= (Processor Busy Time / (Processor Busy Time + Processor Ideal Time)) * 100 \n= ");
    printf("(%d /", t, (float)t);
    printf(" (%d + 0)) * 100\n", t, (float)t);
    printf("= (1 / 1) * 100\n");
    printf("= %d", put);
    printf("%%");
}
