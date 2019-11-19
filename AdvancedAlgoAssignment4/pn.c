#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define debug 0

typedef long LL;

static int k = sizeof(LL)*8 - 1;

LL modexp(LL a, LL b, LL n)
{
    LL c = 0;
    LL d = 1;
    for (int i = k; i >= 0; i--)
    {
        c = 2*c;
        d = (d*d) % n;
        if((b >> i) & 1 == 1)
        {
            c++;
            d = (d*a) % n;
        }
        
        #if debug
        printf("c:%ld d:%ld i: %d bitset: %ld\n", c, d, i, b>>i & 1);
        #endif
    }
    return d;
}

int witness(LL a, LL n)
{
    if(n % 2 == 0 && n != 2) return 1;
    int t = 0;
    LL u;
    LL temp = n-1;
    while(t<32 && (temp & 1) == 0)
    {
        t++;
        temp = temp>>1;
    }
    u = temp;

    #if debug
    // printf("t: %d u: %d\n", t, u);
    #endif 

    LL *x = (LL *) malloc((t+1)*sizeof(LL));
    x[0] = modexp(a, u, n);
    for (int i = 1; i <= t; i++)
    {
        x[i] = (x[i-1]*x[i-1]) % n;
        if(x[i] == 1 && x[i-1] != 1 && x[i-1] != n-1)
        {
            free(x);
            return 1;
        }    
    }

    
    if(x[t] != 1)
    {
        free(x);
        return 1;
    }
    
    free(x);
    return 0;

    
}

int miller_rabin(LL n, int s)
{
    for (int j = 1; j <= s; j++)
    {
        // keep a small if n is large
        int a = (rand() % ((n-1) - 1 + 1)) + 1;

        if(a > 1000)
        {
            a = (rand() % ((1000-1) - 1 + 1)) + 1;
        }
        if(witness(a, n))
        {
            return 0;
        }
    }

    return 1;
}

#if !debug
int main()
{
    int t;
    scanf("%d", &t);

    LL num;
    for (int i = 0; i < t; i++)
    {
        scanf("%ld", &num);
        LL j = num+1;
        while (1)
        {
            if(miller_rabin(j, 50))
            {
                printf("%ld\n", j);
                break;
            }
            j++;
        }
        
    }
    
}
#endif

#if debug
int main()
{
    // for (int i = 0; i < 9; i++)
    // {
    //     printf("%d\n", modexp(3, i, 7));
    // }
    // printf("%d\n", modexp(3,1,7));
    // printf("%d\n", 1>>32);
    srand(0);
    // for (int i = 2; i <= 100; i++)
    // {
    //     if(miller_rabin(i, 10))
    //     {
    //         printf("%d\n", i);
    //     }
    // }
    printf("isprime: %d\n", miller_rabin(10000000019, 10));
    printf("%ld\n", modexp(29205, 50001, 100003));
    printf("%ld\n", (LL) (78517L*78517L));
}
#endif