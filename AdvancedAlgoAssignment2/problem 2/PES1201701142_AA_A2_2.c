#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio_ext.h>

#define DEBUG 0

#define MIN_VAL -1
#define MAX_VAL INT_MAX

int get_max_val(int *numbers, char *symbols, int n)
{

    int **mat = (int **) malloc(n * sizeof(int *));
    for(int i=0; i<n; i++)
    {
        mat[i] = (int *) malloc(n * sizeof(int));
    }

    // base case
    for(int i=0; i<n; i++)
    {
        mat[i][i] = numbers[i];
    }

    for(int l=2; l<=n; l++)
    {
        for(int i=0; i<n-l+1; i++)
        {
            int j = l+i-1;

            mat[i][j] = MIN_VAL;
            for(int k=i; k<j; k++)
            {
                int evaluated;
                if(symbols[k+1] == '*')
                {
                    evaluated = mat[i][k] * mat[k+1][j];
                }
                else
                {
                    evaluated = mat[i][k] + mat[k+1][j];
                }
                
                if(evaluated > mat[i][j])
                {
                    mat[i][j] = evaluated;
                }
            }

            #if DEBUG
            printf("%d ", mat[i][j]);
            #endif
        }

        #if DEBUG
        printf("\n");
        #endif
    }

    int retval = mat[0][n-1];

    for(int i=0; i<n; i++)
    {
        free(mat[i]);
    }
    free(mat);

    return retval;
}

int get_min_val(int *numbers, char *symbols, int n)
{
    // int mat[n][n];

    int **mat = (int **) malloc(n * sizeof(int *));
    for(int i=0; i<n; i++)
    {
        mat[i] = (int *) malloc(n * sizeof(int));
    }

    for(int i=0; i<n; i++)
    {
        mat[i][i] = numbers[i];
    }

    for(int l=2; l<=n; l++)
    {
        for(int i=0; i<n-l+1; i++)
        {
            int j = l+i-1;

            mat[i][j] = MAX_VAL;
            for(int k=i; k<j; k++)
            {
                int evaluated;
                if(symbols[k+1] == '*')
                {
                    evaluated = mat[i][k] * mat[k+1][j];
                }
                else
                {
                    evaluated = mat[i][k] + mat[k+1][j];
                }
                
                if(evaluated < mat[i][j])
                {
                    mat[i][j] = evaluated;
                }
            }

            #if DEBUG
            printf("%d ", mat[i][j]);
            #endif
        }

        #if DEBUG
        printf("\n");
        #endif
    }

    int retval = mat[0][n-1];

    for(int i=0; i<n; i++)
    {
        free(mat[i]);
    }
    free(mat);

    return retval;
}

int main()
{
    int t;
    scanf("%d", &t);

    __fpurge(stdin);

    for(int tests = 0; tests<t; tests++)
    {
        char inpstr[110];
        scanf("%[^\n]s", inpstr);

        __fpurge(stdin);

        int nums[100];
        char sym[100];
        int numlen = 0, symlen = 0;

        char *tempcopy = strdup(inpstr);
        char *st = strtok(inpstr, "+*");
        
        while(st != NULL)   // get the numbers and symbols from the string
        {
            // printf("%s\n", st);
            // printf("%c\n", tempcopy[st - inpstr + strlen(st)]);

            nums[numlen++] = atoi(st);
            char symbol = tempcopy[st - inpstr + strlen(st)];
            if(symbol != 0) 
            {
                sym[++symlen] = symbol;
            }
            st = strtok(NULL, "+*");
        }

        printf("%d %d\n", get_max_val(nums, sym, numlen), get_min_val(nums, sym, numlen));
    }
}
