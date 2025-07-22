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

// Function to plot (generate best and worst case test data)
void plotter(int c)
{
    FILE *f1 = fopen("BestW.txt", "a");
    FILE *f2 = fopen("WorstW.txt", "a");

    for (int n = 1; n <= 10; n++)
    {
        // Initialize graph based on case
        if (c == 1)
        {
            // Best case: Graph with only self-loops
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (i == j)
                        graph[i][j] = 1;
                    else
                        graph[i][j] = 0;
                }
            }
        }
        else if (c == 0)
        {
            // Worst case: Complete graph (all edges exist)
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    graph[i][j] = (i != j) ? 1 : 0; // No self-loops for cleaner worst case
                }
            }
        }
        count = 0;
        warshall(n);
        if (c == 1)
            fprintf(f1, "%d\t%d\n", n, count);
        else
            fprintf(f2, "%d\t%d\n", n, count);
    }
    fclose(f1);
    fclose(f2);
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
        printf("Generating best and worst case data...\n");
        for (int i = 0; i < 2; i++)
            plotter(i);
        printf("Data files created: BestW.txt and WorstW.txt\n");
        break;
    default:
        printf("Invalid choice!\n");
    }

    return 0;
}
