#include <stdio.h>
void line(int nf)
{
    if (nf == 1 || nf == 2)
    {
        printf("\n|---------------------------------");
    }
    else if (nf >= 3)
    {
        printf("\n|---------------------------------");

        for (int i = 3; i <= nf; i++)
        {
            printf("------");
        }
    }
    printf("|");
}
void midline(int nf)
{
    if (nf == 1 || nf == 2)
    {
        printf("\n|        -------------            |");
    }
    else if (nf >= 3)
    {
        printf("\n|        -------------");
        for (int i = 3; i <= nf; i++)
        {
            printf("------");
        }
        printf("            |");
    }
}
void Firstline(int nf)
{
    if (nf == 1 || nf == 2)
    {
        line(nf);
        printf("\n|Refrence|Page Frames| Page Fault |");
        midline(nf);
        printf("\n|        | Frame No. |      /     |");
    }
    else
    {
        line(nf);
        printf("\n|Refrence|");
        for (int i = 3; i <= nf; i++)
        {
            printf("   ");
        }
        printf("Page  frames  ");
        for (int i = 4; i <= nf; i++)
        {
            printf("   ");
        }
        printf("| Page Fault |");
        midline(nf);
        printf("\n|        |");
        for (int i = 3; i <= nf; i++)
        {
            printf("   ");
        }
        printf("Frame number  ");
        for (int i = 4; i <= nf; i++)
        {
            printf("   ");
        }
        printf("|      /     |");
    }
}

void call(int n, int pg[])
{
    int fr[10], nf, op;
    int count[10], i, j, k, fault, f, flag, temp, current, c, dist, max, m, cnt, p, x, avail;
    int tmp1[10], tmp2[10];
    fault = 0;
    dist = 0;
    k = 0;
    int hitflag = 0;
    char ans;

    printf("Select Any one option from the following for number of Page Frames : ");
    printf("\n1) N Frames\n2) 3 Frames \n3) 4 Frames \n4) 5 Frames \n5) EXIT \n");
    printf("Enter Your Choice:");
    scanf("%d", &op);
    if (op == 5)
    {
        return 0;
    }
    else if (op != 5)
    {
        if (op == 1)
        {
            printf("Enter the number of Frames(N) :");
            scanf("%d", &f);
        }
        else if (op == 2)
        {
            f = 3;
        }
        else if (op == 3)
        {
            f = 4;
        }
        else if (op == 4)
        {
            f = 5;
        }
        Firstline(f);
        midline(f);
        printf("\n| String ");
        for (i = 1; i <= f; i++)
        {
            printf("|%3d  ", i);
            tmp1[i] = 0;
        }
        printf("| Page Hit   |");
        line(f);
        for (i = 0; i < f; i++)
        {
            count[i] = 0;
            fr[i] = -1;
        }
        for (i = 0; i < n; i++)
        {
            flag = 0;
            temp = pg[i];
            for (j = 0; j < f; j++)
            {
                if (temp == fr[j])
                {
                    flag = 1;
                    break;
                }
            }
            if ((flag == 0) && (k < f))
            {
                fault++;
                fr[k] = temp;
                k++;
            }
            else if ((flag == 0) && (k == f))
            {
                fault++;
                for (cnt = 0; cnt < f; cnt++)
                {
                    current = fr[cnt];
                    for (c = i; c < n; c++)
                    {
                        if (current != pg[c])
                            count[cnt]++;
                        else
                            break;
                    }
                }
                max = 0;
                for (m = 0; m < f; m++)
                {
                    if (count[m] > max)
                    {
                        max = count[m];
                        p = m;
                    }
                }
                fr[p] = temp;
            }
            printf("\n|   %d\t |", pg[i]);
            for (x = 0; x < f; x++)
            {
                printf("%4d |", fr[x]);
                tmp2[x] = fr[x];
                if (tmp1[x] != tmp2[x])
                {
                    hitflag = 1;
                }
            }
            if (hitflag == 1)
            {
                printf("%5c       |", 'P');
            }
            else
            {
                printf("%5c       |", 'H');
            }
            for (int i = 0; i < f; i++)
            {
                tmp1[i] = tmp2[i];
            }
            hitflag = 0;
        }

        line(f);
        int hit = n - fault;
        float pfr = ((float)fault / (float)n) * 100;
        float phr = ((float)hit / (float)n) * 100;
        printf("\n\n1) Total number of page faults \n\t= (Total No. of Pages - Total No.of Page Hits) \n\t= (%d - %d) \n\t= %d", n, hit, fault);
        printf("\n2) Total number of page hits \n\t= (Total No. of Pages - No.of Page Faults) \n\t= (%d - %d) \n\t= %d", n, fault, hit);
        printf("\n3) Page Fault Rate \n\t= (Total No. of Page Fault / Total No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)fault, (float)n, pfr);
        printf("\n4) Page Hit Rate \n\t= (Total No. of Page Hits / Total No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)hit, (float)n, phr);
        printf("\n\nDo You Want to Continue...?(Y/N) :");
        scanf("%s", &ans);
        if (ans == 'N')
        {
            return 0;
        }
        else if (ans == 'Y')
        {
            call(n, pg);
        }
    }
}
int main()
{
    int n, i, pg[100];
    printf("Enter the total no. of pages:");
    scanf("%d", &n);
    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pg[i]);
    call(n, pg);
}
