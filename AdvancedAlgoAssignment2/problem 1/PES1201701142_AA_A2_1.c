#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print_seq(int **s, int m, int bestLast);
int get_min_col(int **arr, int n, int col);

int main()
{
    int n, m;

    scanf("%d%d", &n, &m);

    int *en = (int *)malloc((n + 1) * sizeof(int));    //entry costs
    int *ex = (int *)malloc((n + 1) * sizeof(int));    //exit costs
    int **a = (int **)malloc((n + 1) * sizeof(int *)); //costs matrix

    // scanf values into a
    for (int i = 1; i <= n; i++)
    {
        a[i] = (int *)malloc((m + 1) * sizeof(int));

        scanf("%d%d", &en[i], &ex[i]);
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    // scanf transfer costs
    int **trans = (int **)malloc((2 * (n - 1) + 1) * sizeof(int *));
    for (int i = 1; i <= 2 * (n - 1); i++)
    {
        trans[i] = (int *)malloc(m * sizeof(int));
        for (int j = 1; j <= m - 1; j++)
        {
            scanf("%d", &trans[i][j]);
        }
    }

    int **f = (int **)malloc((n + 1) * sizeof(int *)); //2d array to store min cost to reach f[i][j]
    for (int i = 1; i <= n; i++)
    {
        f[i] = (int *)malloc((m + 1) * sizeof(int));
    }

    int **s = (int **)malloc((n + 1) * sizeof(int *)); //solution 2d array
    for (int i = 1; i <= n; i++)
    {
        s[i] = (int *)malloc((m + 1) * sizeof(int));
    }

    // main algorithm

    // initialize entry costs
    for (int i = 1; i <= n; i++)
    {
        f[i][1] = en[i] + a[i][1];
    }

    for (int j = 2; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            //two corner cases, top line and bottom line
            if (i == 1)
            {
                int x1 = f[i][j - 1] + a[i][j];
                int x2 = INT_MAX;
                if (n > 1)
                    x2 = f[i + 1][j - 1] + a[i][j] + trans[2][j - 1];

                if (x1 < x2)
                {
                    f[i][j] = x1;
                    s[i][j] = i;
                }
                else
                {
                    f[i][j] = x2;
                    s[i][j] = i + 1;
                }
            }
            else if (i == n)
            {
                int x1 = f[i][j - 1] + a[i][j];
                int x2 = f[i - 1][j - 1] + a[i][j] + trans[2 * n - 2 - 1][j - 1];

                if (x1 < x2)
                {
                    f[i][j] = x1;
                    s[i][j] = i;
                }
                else
                {
                    f[i][j] = x2;
                    s[i][j] = i - 1;
                }
            }
            else    // case when we have a line above and below
            {
                int x1 = f[i][j - 1] + a[i][j];
                int x2 = f[i - 1][j - 1] + a[i][j] + trans[2 * (i - 1) - 1][j - 1];
                int x3 = f[i + 1][j - 1] + a[i][j] + trans[2 * (i + 1) - 2][j - 1];

                if(x1 < x2)
                {
                    if(x1 < x3)
                    {
                        f[i][j] = x1;
                        s[i][j] = i;
                    }
                    else
                    {
                        f[i][j] = x3;
                        s[i][j] = i+1;
                    }
                }
                else
                {
                    if(x2 < x3)
                    {
                        f[i][j] = x2;
                        s[i][j] = i-1;
                    }
                    else
                    {
                        f[i][j] = x3;
                        s[i][j] = i+1;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        f[i][m] += ex[i];
    }
    
    
    int bestLast = get_min_col(f, n, m);
    printf("%d\n", f[bestLast][m]);
    print_seq(s, m, bestLast);

    free(en);
    free(ex);
    free(a);
    free(f);
    free(s);

}

void print_seq(int **s, int m, int bestLast)
{
    if(m == 1)
    {
        printf("%d\n", bestLast);
        return;
    }
    int v = s[bestLast][m];
    print_seq(s, m-1, v);
    printf("%d\n", bestLast);
}

int get_min_col(int **arr, int n, int col)
{
    int idx = -1;
    int val = INT_MAX;

    for(int i=1; i<=n; i++)
    {
        if(arr[i][col] < val)
        {
            val = arr[i][col];
            idx = i;
        }
    }

    return idx;
}