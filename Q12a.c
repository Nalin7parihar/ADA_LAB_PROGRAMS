#include <stdio.h>
#include <stdlib.h>

#define MAX 100
int graph[MAX][MAX], count = 0;

// Warshall's Algorithm to compute transitive closure
void warshall(int n)
{
    count = 0; // Reset count for each run
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                count++; // Count each comparison operation
                if (graph[i][k] && graph[k][j])
                {
                    graph[i][j] = 1;
                }
            }
        }
    }
}

// Function to generate plot data
void plotter()
{
    FILE *f1 = fopen("Warshall.txt", "w");

    if (!f1)
    {
        printf("Error creating file\n");
        return;
    }

    for (int n = 1; n <= 10; n++)
    {
        // Initialize with a simple graph (complexity remains O(n^3))
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    graph[i][j] = 0;                       // No self-loops
                else if (j == i + 1 || (i == n && j == 1)) // Simple cycle
                    graph[i][j] = 1;
                else
                    graph[i][j] = 0;
            }
        }

        count = 0;
        warshall(n);
        fprintf(f1, "%d\t%d\n", n, count);
    }

    fclose(f1);
    printf("Plot data file created: Warshall.txt\n");
}

// Interactive tester function for user input
void tester()
{
    int n;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize graph to 0
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            graph[i][j] = 0;
        }
    }

    printf("Enter the adjacency matrix (%dx%d):\n", n, n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nOriginal adjacency matrix:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    warshall(n);

    printf("\nTransitive closure matrix:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    printf("Total operations performed: %d\n", count);
}

int main()
{
    int choice;

    printf("Warshall's Algorithm - Transitive Closure\n");
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
