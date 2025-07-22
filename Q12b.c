#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF 99999 // Represents infinity (no direct path)

int graph[MAX][MAX], count = 0;

// Floyd's Algorithm to find shortest paths between all pairs of vertices
void floyd(int n)
{
    count = 0; // Reset count for each run

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                count++; // Count each comparison operation
                if (graph[i][k] != INF && graph[k][j] != INF &&
                    graph[i][k] + graph[k][j] < graph[i][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

// Interactive tester function for user input
void tester()
{
    int n;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (use %d for infinity/no path):\n", INF);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nOriginal cost matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("%8s", "INF");
            else
                printf("%8d", graph[i][j]);
        }
        printf("\n");
    }

    floyd(n);

    printf("\nAll-pairs shortest path matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("%8s", "INF");
            else
                printf("%8d", graph[i][j]);
        }
        printf("\n");
    }

    printf("Total operations performed: %d\n", count);
}

void plotter()
{
    FILE *f1 = fopen("Floyd.txt", "w");

    if (!f1)
    {
        printf("Error creating file\n");
        return;
    }

    for (int n = 2; n <= 10; n++)
    {
        // Initialize with a simple graph (complexity remains O(n^3))
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    graph[i][j] = 0;
                else if (j == i + 1) // Chain: 0->1->2->...->n-1
                    graph[i][j] = 1;
                else
                    graph[i][j] = INF;
            }
        }

        floyd(n);
        fprintf(f1, "%d\t%d\n", n, count);
    }

    fclose(f1);
    printf("Plot data file created: Floyd.txt\n");
}

int main()
{
    int choice;

    printf("Floyd's Algorithm - All Pairs Shortest Path\n");
    printf("1. Interactive Tester\n");
    printf("2. Generate Plot Data\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        tester();
        break;
    case 2:
        printf("Generating plot data...\n");
        plotter();
        break;
    default:
        printf("Invalid choice!\n");
    }

    return 0;
}
