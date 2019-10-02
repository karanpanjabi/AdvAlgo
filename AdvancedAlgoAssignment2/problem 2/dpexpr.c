#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0

typedef long long LL;

#define MIN_VAL -1
#define MAX_VAL 1000000

LL get_max_val(int *numbers, char *symbols, int n)
{
    LL mat[n][n];

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
                LL evaluated;
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
            printf("%lld ", mat[i][j]);
            #endif
        }

        #if DEBUG
        printf("\n");
        #endif
    }

    return mat[0][n-1];
}

LL get_min_val(int *numbers, char *symbols, int n)
{
    LL mat[n][n];

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
                LL evaluated;
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
            printf("%lld ", mat[i][j]);
            #endif
        }

        #if DEBUG
        printf("\n");
        #endif
    }

    return mat[0][n-1];
}

int main()
{
    char inpstr[110];
    scanf("%[^\n]s ", inpstr);

    int nums[100];
    char sym[100];
    int numlen = 0, symlen = 0;

    char *tempcopy = strdup(inpstr);
    char *st = strtok(inpstr, "+*");
    
    while(st != NULL)
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

    printf("%lld %lld\n", get_max_val(nums, sym, numlen), get_min_val(nums, sym, numlen));
}
