#include <stdio.h>
#include <stdlib.h>
void line(int nf)
{
    if (nf >= 3)
    {
        printf("\n|---------------------------------");
    }
    for (int i = 3; i <= nf; i++)
    {
        printf("------");
    }
    printf("|");
}
void midline(int nf)
{
    if (nf >= 3)
    {
        printf("\n|        -------------");
    }
    for (int i = 3; i <= nf; i++)
    {
        printf("------");
    }
    printf("            |");
}
void Firstline(int nf)
{
    if (nf == 3)
    {
        line(nf);
        printf("\n|Refrence|   Page  frames  | Page Fault |");
    }
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
int main()
{
    start:
    printf("\n");
    int i=0, j=0, l=0, rs[25], frame[10], nf=0, k=0, avail=0, count = 0, hit = 0, ca=0;
    float pfr = 0, phr = 0;
    char ch[10];


    printf("Enter the length of Reference String: ");
    scanf("%d", &l);
    printf("Enter Reference String:\n");
    for (i = 1; i <= l; i++)
        scanf("%d", &rs[i]);

    printf("\n Enter page number as following: \n");
    printf("1) Enter N frame\n");
    printf("2) 3 Frame\n");
    printf("3) 4 Frame\n");
    printf("4) 5 Frame\n");
    printf("5) Exit\n");
    printf("Enter any choise: ");
    scanf("%d", &ca);

    switch (ca)
    {
        case 1:
            printf("Enter the number of Frames: ");
            scanf("%d", &nf);
            break;
        case 2:
            nf = 3;
            break;
        case 3:
            nf = 4;
            break;
        case 4:
            nf = 5;
            break;
        case 5:
            exit(1);

        default:
            printf("Enter valid number between 1 to 5\n");
            break;
    }
    for (i = 0; i < nf; i++)
        frame[i] = -1;
    j = 0;

    Firstline(nf);
    midline(nf);
    printf("\n| String ");
    for (i = 1; i <= nf; i++)
    {
        printf("|%3d  ", i);
    }
    printf("| Page Hit   |");
    line(nf);

    for (i = 1; i <= l; i++)
    {
        printf("\n|   %d\t |", rs[i]);
        avail = 0;
        for (k = 0; k < nf; k++)
            if (frame[k] == rs[i])
                avail = 1;
        if (avail == 0)
        {
            frame[j] = rs[i];
            j = (j + 1) % nf;
            count++;
            for (k = 0; k < nf; k++)
                printf("%4d |", frame[k]);
            printf("%5c       |", 'P');
        }
        else
        {
            for (k = 0; k < nf; k++)
                printf("     |");
            printf("%5c       |", 'H');
        }
    }
    line(nf);
    hit = l - count;
    pfr = ((float)count / (float)l) * 100;
    phr = ((float)hit / (float)l) * 100;
    printf("\n\n1) Total number of page faults\n\t = Total Page - Page Hit\n\t = %d - %d \n\t = %d", l, hit, count);
    printf("\n2) Total number of page hits\n\t = Total Page - Page Fault\n\t = %d - %d \n\t = %d", l, count, hit);
    printf("\n3) Page Fault Rate \n\t= (No. of Page Faults / No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)count, (float)l, pfr);
    printf("\n4) Page Hit Rate \n\t= (No. of Page Hits / No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)hit, (float)l, phr);

    printf("\n\nDo you want to contine? (y/n)\n");
    scanf("%s", ch);

    if(strcmp(ch, "y") == 0)
    {
        goto start;
    }
    
    return 0;
}
