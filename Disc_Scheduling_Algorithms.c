#include <stdio.h>
#include <stdlib.h>

void fcfs(int n, int head, int requests[])
{
    int total_head_movement = 0;
    printf("\nFCFS (First-Come, First-Served) Disk Scheduling Algorithm\n");
    printf("Request Queue: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
    }
    printf("\n");
    printf("Initial Head Position: %d\n", head);
    printf("Sequence of Movement: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
        total_head_movement += abs(requests[i] - head);
        head = requests[i];
    }
    printf("\nTotal Head Movement: %d Cylinders\n", total_head_movement);
}

void sstf(int n, int head, int requests[])
{
    int total_head_movement = 0;
    printf("\nSSTF (Shortest Seek Time First) Disk Scheduling Algorithm\n");
    printf("Request Queue: ");
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
    }
    printf("\n");
    printf("Initial Head Position: %d\n", head);
    printf("Sequence of Movement: ");

    int completed[n];
    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int min_distance = 999999;
        int min_index = -1;
        for (int j = 0; j < n; j++)
        {
            if (!completed[j])
            {
                int distance = abs(requests[j] - head);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }
        printf("%d ", requests[min_index]);
        total_head_movement += min_distance;
        head = requests[min_index];
        completed[min_index] = 1;
    }
    printf("\nTotal Head Movement: %d Cylinders\n", total_head_movement);
}
void scan(int n, int head, int requests[], int direction)
{
    int total_head_movement = 0;
    printf("\nSCAN (Elevator) Disk Scheduling Algorithm\n");
    printf("Request Queue: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
    }
    printf("\n");
    printf("Initial Head Position: %d\n", head);
    printf("Direction: %s\n", direction == 1 ? "RIGHT" : "LEFT");
    printf("Sequence of Movement: ");

    int completed[n];
    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }

    int current = head;
    int found = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int head_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (requests[i] == head)
        {
            head_index = i;
            break;
        }
    }
    if (direction == 1)
    {
        for (int i = head_index; i < n; i++)
        {
            if (requests[i] > head)
            {
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                printf("%d ", current);
                completed[i] = 1;
            }
        }

        printf("199 ");
        total_head_movement += abs(199 - current);
        current = 199;
        found = 1;
        for (int i = n; i > head_index; i--)
        {
            if (requests[i] < head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }
    }
    else
    {
        for (int i = n; i > head_index; i--)
        {
            if (requests[i] < head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }
        printf("0 ");
        total_head_movement += abs(0 - current);
        current = 0;
        found = 1;
        for (int i = head_index; i < n; i++)
        {
            if (requests[i] > head)
            {
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                printf("%d ", current);
                completed[i] = 1;
            }
        }
    }
    if (!found)
    {
        printf("%d ", head);
        total_head_movement += abs(head - current);
    }

    printf("\nTotal Head Movement: %d Cylinders\n", total_head_movement);
}
void c_scan(int requests[], int n, int head, int direction)
{
    int total_head_movement = 0;
    printf("\nC-SCAN (Elevator) Disk Scheduling Algorithm\n");
    printf("Request Queue: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
    }
    printf("\n");
    printf("Initial Head Position: %d\n", head);
    printf("Direction: %s\n", direction == 1 ? "RIGHT" : "LEFT");
    printf("Sequence of Movement: ");

    int completed[n];
    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }

    int current = head;
    int found = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int head_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (requests[i] == head)
        {
            head_index = i;
            break;
        }
    }
    if (direction == 1)
    {
        for (int i = head_index; i < n; i++)
        {
            if (requests[i] > head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }

        printf("199 ");
        total_head_movement += abs(199 - current);
        current = 199;
        found = 1;
        printf("0 ");
        for (int i = 0; i < n - 2; i++)
        {
            if (requests[i] < head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }
    }
    else
    {
        for (int i = n; i > head_index; i--)
        {
            if (requests[i] < head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }
        printf("0 ");
        total_head_movement += abs(requests[0] - current);
        current = 0;
        found = 1;
        for (int i = n - 1; i > head_index; i--)
        {
            if (requests[i] > head)
            {
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                printf("%d ", current);
                completed[i] = 1;
            }
        }
    }
    if (!found)
    {
        printf("%d ", head);
        total_head_movement += abs(head - current);
    }

    printf("\nTotal Head Movement: %d Cylinders\n", total_head_movement);
}

void look(int n, int head, int requests[], int direction)
{
    int total_head_movement = 0;
    printf("\nLOOK Disk Scheduling Algorithm\n");
    printf("Request Queue: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
    }
    printf("\n");
    printf("Initial Head Position: %d\n", head);
    printf("Direction: %s\n", direction == 1 ? "RIGHT" : "LEFT");
    printf("Sequence of Movement: ");

    int completed[n];
    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }

    int current = head;
    int found = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int head_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (requests[i] == head)
        {
            head_index = i;
            break;
        }
    }
    if (direction == 1)
    {
        for (int i = head_index; i < n; i++)
        {
            if (requests[i] > head)
            {
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                printf("%d ", current);
                completed[i] = 1;
            }
        }

        found = 1;
        for (int i = n; i > head_index; i--)
        {
            if (requests[i] < head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }
    }
    else
    {
        for (int i = n; i > head_index; i--)
        {
            if (requests[i] < head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }
        found = 1;
        for (int i = head_index; i < n; i++)
        {
            if (requests[i] > head)
            {
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                printf("%d ", current);
                completed[i] = 1;
            }
        }
    }
    if (!found)
    {
        printf("%d ", head);
        total_head_movement += abs(head - current);
    }

    printf("\nTotal Head Movement: %d Cylinders\n", total_head_movement);
}
void c_look(int n, int head, int requests[], int direction)
{
    int total_head_movement = 0;
    printf("\nC-LOOK Disk Scheduling Algorithm\n");
    printf("Request Queue: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", requests[i]);
    }
    printf("\n");
    printf("Initial Head Position: %d\n", head);
    printf("Direction: %s\n", direction == 1 ? "RIGHT" : "LEFT");
    printf("Sequence of Movement: ");

    int completed[n];
    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }

    int current = head;
    int found = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int head_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (requests[i] == head)
        {
            head_index = i;
            break;
        }
    }
    if (direction == 1)
    {
        for (int i = head_index; i < n; i++)
        {
            if (requests[i] > head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }

        found = 1;
        for (int i = 0; i < n - 2; i++)
        {
            if (requests[i] < head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }
    }
    else
    {
        for (int i = n; i > head_index; i--)
        {
            if (requests[i] < head)
            {
                printf("%d ", requests[i]);
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                completed[i] = 1;
            }
        }
        found = 1;
        for (int i = n - 1; i > head_index; i--)
        {
            if (requests[i] > head)
            {
                total_head_movement += abs(requests[i] - current);
                current = requests[i];
                printf("%d ", current);
                completed[i] = 1;
            }
        }
    }
    if (!found)
    {
        printf("%d ", head);
        total_head_movement += abs(head - current);
    }

    printf("\nTotal Head Movement: %d Cylinders\n", total_head_movement);
}

int askToContinue()
{
    char choice;
    printf("\nDo you want to continue? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
    {
        return 1;
    }
    else if (choice == 'n' || choice == 'N')
    {
        return 0;
    }
    else
    {
        printf("\nWrong Input! Try again...\n");
        askToContinue();
        return -1;
    }
}

int main()
{
    int n;
    int head;
    int direction;
    int continueLoop = 1;
    char ch;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }
    while (continueLoop)
    {
        printf("\nChoose any option: \n(A) FCFS\n(B) SSTF\n(C) SCAN\n(D) C-SCAN\n(E) LOOK\n(F) C-LOOK\n(G) Exit\n");
        printf("\nEnter your choice: ");
        scanf("\n%c", &ch);
        switch (ch)
        {
        case 'A':
            fcfs(n, head, requests);
            break;
        case 'B':
            sstf(n, head, requests);
            break;
        case 'C':
            printf("Enter the direction (1 for RIGHT or -1 for LEFT): ");
            scanf("%d", &direction);
            scan(n, head, requests, direction);
            break;
        case 'D':
            printf("Enter the direction (1 for RIGHT or -1 for LEFT): ");
            scanf("%d", &direction);
            c_scan(requests, n, head, direction);
            break;
        case 'E':
            printf("Enter the direction (1 for RIGHT or -1 for LEFT): ");
            scanf("%d", &direction);
            look(n, head, requests, direction);
            break;
        case 'F':
            printf("Enter the direction (1 for RIGHT or -1 for LEFT): ");
            scanf("%d", &direction);
            c_look(n, head, requests, direction);
            break;
        case 'G':
            exit(0);
            break;
        default:
            printf("\nWrong Input!\n");
            break;
        }
        if (continueLoop)
        {
            continueLoop = askToContinue();
        }
    }
    return 0;
}
