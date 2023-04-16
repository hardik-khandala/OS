#include <stdio.h>
#include <limits.h>
int count = 0;
int checkHit(int incomingPage, int queue[], int occupied)
{
    for (int i = 0; i < occupied; i++)
    {
        if (incomingPage == queue[i])
            return 1;
    }

    return 0;
}

void printFrame(int queue[], int occupied)
{
    for (int i = 0; i < occupied; i++)
    {
        printf("%4d |", queue[i]);
    }
    for (int i = count-1; i >0; i--)
    {
        printf("%4d |", -1);
    }
    count--;   
}
void line(int nf)
{
    if (nf >=3)
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
    int ca;
    char ch[10];

    start:
    printf("Enter the number of Pages: ");
    int nop;
    scanf("%d", &nop);
    int incomingStream[nop];
    printf("Enter Page Reference String:\n");
    for (int i = 0; i < nop; i++)
    {
        scanf("%d", &incomingStream[i]);
    }

    int frames;
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
            scanf("%d", &frames);
            break;
        case 2:
            frames = 3;
            break;
        case 3:
            frames = 4;
            break;
        case 4:
            frames = 5;
            break;
        case 5:
            exit(1);

        default:
            printf("Enter valid number between 1 to 5\n");
            break;
    }
    count=frames;
    int n = sizeof(incomingStream) / sizeof(incomingStream[0]);
    int queue[n];
    int distance[n];
    int occupied = 0;
    int pagefault = 0;
    Firstline(frames);
    midline(frames);
    printf("\n| String ");
    for (int i = 1; i <= frames; i++)
    {
        printf("|%3d  ", i);
    }
    printf("| Page Hit   |");
    line(frames);
    for (int i = 0; i < n; i++)
    {
        printf("\n|   %d\t |", incomingStream[i]);

        if (checkHit(incomingStream[i], queue, occupied))
        {
            printFrame(queue, occupied);
            printf("%5c       |", 'H');
        }
        else if (occupied < frames)
        {
            queue[occupied] = incomingStream[i];
            pagefault++;
            occupied++;

            printFrame(queue, occupied);
            printf("%5c       |", 'P');
        }
        else
        {
            int max = INT_MIN;
            int index;
            for (int j = 0; j < frames; j++)
            {
                distance[j] = 0;
                for (int k = i - 1; k >= 0; k--)
                {
                    ++distance[j];

                    if (queue[j] == incomingStream[k])
                        break;
                }
                if (distance[j] > max)
                {
                    max = distance[j];
                    index = j;
                }
            }
            queue[index] = incomingStream[i];
            printFrame(queue, occupied);
            printf("%5c       |", 'F');
            pagefault++;
        }
    }

    line(frames);
    printf("\n");

    int hit = n - pagefault;
    float pfr = ((float)pagefault / (float)n) * 100;
    float phr = ((float)hit / (float)n) * 100;
    printf("\n\n1) Total no. of page faults\n\t = (Total No. of Page - Total No. of Page Hits) \n\t = %d - %d \n\t = %d",n ,hit ,pagefault);
    printf("\n2) Total no. of page hits\n\t = (Total No. of Page - Total No. of Page faults) \n\t = %d - %d \n\t = %d",n ,pagefault, hit);
    printf("\n3) Page Fault Rate \n\t= (Total No. of Page Fault / Total No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)pagefault, (float)n, pfr);
    printf("\n4) Page Hit Rate \n\t= (Total No. of Page Hit / Total No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)hit, (float)n, phr);
    printf("\n");

    printf("Do you want to continue? (y/n)\n");
    scanf("%s", ch);

    if(strcmp(ch, "y") == 0)
    {
        goto start;
    }

    return 0;
}
