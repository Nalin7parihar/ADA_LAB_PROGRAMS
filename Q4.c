#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int count = 0;
bool stringmatching(char *text, char *pattern, int n, int m)
{
    count = 0;
    for (int i = 0; i <= (n - m); i++)
    {
        int j = 0;
        while (j < m)
        {
            count++;
            if (pattern[j] != text[i + j])
                break;
            j++;
        }
        if (j == m)
            return true;
    }
    return false;
}

void plotter()
{
    FILE *f1 = fopen("strbest.txt", "w");
    FILE *f2 = fopen("strworst.txt", "w");
    FILE *f3 = fopen("stravg.txt", "w");
    char *text = (char *)malloc(1000 * sizeof(char));
    char *pattern;
    for (int i = 0; i < 1000; i++)
        *(text + i) = 'a';
    int m, n;
    n = 1000;
    m = 10;
    while (m <= 1000)
    {
        pattern = (char *)malloc(m * sizeof(char));
        count = 0;
        for (int i = 0; i < m; i++) // best case
            pattern[i] = 'a';
        stringmatching(text, pattern, n, m);
        fprintf(f1, "%d\t%d\n", m, count);

        count = 0;
        pattern[m - 1] = 'b'; // worst case
        stringmatching(text, pattern, n, m);
        fprintf(f2, "%d\t%d\n", m, count);

        count = 0;
        for (int i = 0; i < m; i++) // avg case
            pattern[i] = 97 + rand() % 3;
        stringmatching(text, pattern, n, m);
        fprintf(f3, "%d\t%d\n", m, count);
        free(pattern);
        if (m < 100)
            m = m + 10;
        else
            m = m + 100;
    }
}

void tester()
{
    char text[100], pattern[100];

    printf("Enter the pattern: ");
    scanf("%s", pattern);

    printf("Enter the text: ");
    scanf("%s", text);

    int m = strlen(pattern);
    int n = strlen(text);

    bool result = stringmatching(text, pattern, n, m);

    if (result)
    {
        printf("\nPattern '%s' found in text '%s'\n", pattern, text);
        printf("Number of comparisons: %d\n", count);
    }
    else
    {
        printf("\nPattern '%s' not found in text '%s'\n", pattern, text);
        printf("Number of comparisons: %d\n", count);
    }
}

void main()
{
    int ch;
    printf("Enter \n1.Tester\n2.Plotter\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice.\n");
    }
}