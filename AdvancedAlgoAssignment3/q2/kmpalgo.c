#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0

int *compute_prefix_function(char *pattern, int patlen)
{
    int m = patlen;
    int *pi = (int *)malloc((m + 1) * sizeof(int));

    pi[1] = 0;
    int k = 0;
    for (int q = 2; q <= m; q++)
    {
        while (k > 0 && pattern[k + 1] != pattern[q])
        {
            k = pi[k];
        }
        if (pattern[k+1] == pattern[q])
        {
            k++;
        }
        pi[q] = k;
    }

    return pi;
}

void kmp_matcher(char *text, char *pattern)
{
    int n = strlen(text) - 1;
    int m = strlen(pattern) - 1;
    int *pi = compute_prefix_function(pattern, m);

    int found = 0;

    int q = 0;
    for (int i = 1; i <= n; i++)
    {
        while(q > 0 && pattern[q+1] != text[i])
        {
            q = pi[q];
        }
        if(pattern[q+1] == text[i])
        {
            q = q+1;
        }
        if(q == m)
        {
            found = 1;
            printf("%d ", i-m);
            q = pi[q];
        }
    }

    if(!found)
    {
        printf("-1\n");
    }
    else
    {
        printf("\n");
    }
    

    free(pi);
    
}

void to_lower(char *text)
{
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] += 32;
    }
}

int main()
{
    char text[4010];
    text[0] = '_';
    scanf("%[^\n]s", text + 1);
    getchar();
    to_lower(text);

    #if DEBUG
    printf("Text: %s\n", text);
    #endif

    int t;
    scanf("%d", &t);
    getchar();

    #if DEBUG
    printf("t: %d\n", t);
    #endif

    for (int tests = 0; tests < t; tests++)
    {
        char pattern[1010];
        pattern[0] = '_';
        scanf("%[^\n]s", pattern + 1);
        getchar();
        to_lower(pattern);

        #if DEBUG
        printf("Pattern: %s\n", pattern);
        #endif

        kmp_matcher(text, pattern);
    }
}
