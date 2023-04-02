#include <stdio.h>

struct process
{
    int size;
    int set;
    int holeid;
} p[10];

struct hole
{
    int hid;
    int size;
    int actual;
    int set;
} h[10];

void sorthole(struct hole a[], int n)
{
    struct hole temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i].size < a[j].size)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int enterhole(struct hole a[])
{
    int n;
    printf("Enter the number of Holes : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter size for hole H%d : ", i);
        scanf("%d", &a[i].size);
        a[i].actual = a[i].size;
        a[i].hid = i;
        a[i].set = 0;
    }
    return n;
}

int enterprocess(struct process a[])
{
    int n;
    printf("\nEnter number of process : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("enter the size of process P%d : ", i);
        scanf("%d", &a[i].size);
        a[i].set = 0;
    }
    return n;
}
void calcu(struct hole a[], struct process b[], int no_h, int no_p)
{
    for (int i = 0; i < no_p; i++)
    {
        sorthole(a, no_h);
        for (int j = 0; j < no_h; j++)
        {
            if (b[i].set != 1 && a[j].set != 1)
            {
                if (b[i].size <= a[j].size)
                {
                    b[i].set = 1;
                    a[j].set = 1;
                    b[i].holeid = a[j].hid;
                    a[j].size -= b[i].size;
                }
            }
        }
    }
}

void out(struct hole a[], struct process b[], int no_h, int no_p)
{
    printf("\n\t\t\t\t\tWorst Fit\n");
    printf("=========================================================================================");
    printf("\n|\tProcess ID\t|\tProcess Required Memory Size\t|\tHole Allocated\t|\n");
    printf("=========================================================================================\n");
    for (int i = 0; i < no_p; i++)
    {
        if (b[i].set != 1)
        {
            printf("|\t     P%d     \t|\t\t%d\t\t\t|\tNot allocated\t|", i, b[i].size);
            printf("\n-----------------------------------------------------------------------------------------\n");
        }
        else
        {
            printf("|\t     P%d     \t|\t\t%d\t\t\t|\tH%d\t\t|", i, b[i].size, b[i].holeid);
            printf("\n-----------------------------------------------------------------------------------------\n");
        }
    }
    printf("\n\n=================================================================================================");
    printf("\n|\tHole ID\t|\tActual Memory Size Allocated\t|\tAvailable Free Memory Size\t|\n");
    printf("=================================================================================================\n");
    int vest = 0;
    int vest1 = 0;
    for (int i = 0; i < no_h; i++)
    {
        vest1 = vest1 + a[i].size;
        if (a[i].set != 1)
        {
            printf("|\tH%d\t|\t\t%d\t\t\t|\t\t-\t\t\t|", a[i].hid, a[i].actual);
            printf("\n-------------------------------------------------------------------------------------------------\n");
        }
        else
        {
            vest = vest + a[i].size;
            printf("|\tH%d\t|\t\t%d\t\t\t|\t\t%d\t\t\t|", a[i].hid, a[i].actual, a[i].size);
            printf("\n-------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("\t\t\t\t\t\tTotal = |\t\t%d\t\t\t|\n", vest);
    printf("\t\t\t\t\t\t\t-----------------------------------------\n\n\n");
    printf("Total Internal Fragmentation is %d MB.\n\n", vest);
    printf("Total Un-utilized Memory is %d MB.\n\n", (vest1 - vest));
    printf("Total Memory Available is %d MB.\n\n", vest1);
    for (int i = 0; i < no_p; i++)
    {
        if (b[i].set != 1)
        {
            printf("\n->    P%d     Not allocated", i);
        }
        else
        {
            printf("\n->    P%d     Allocated to      H%d", i, b[i].holeid);
        }
    }
}

int main()
{
    int no_h, no_p;
    no_h = enterhole(h);
    no_p = enterprocess(p);
    calcu(h, p, no_h, no_p);
    out(h, p, no_h, no_p);

    return 0;
}
