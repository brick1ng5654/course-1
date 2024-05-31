#include <stdio.h>
#include <limits.h>
int main()
{
    unsigned long n, x=0, y=1, z=0, i, mx=1;

    printf("n=");
    scanf("%lu",&n);

    if (n == 0 || n==1) {
        printf("F(%lu)=%lu\n",n, n);
    } else {
        for(i=2; i<=n;i++)
        {
            z=x+y;
            x=y;
            y=z;
        }
        printf("F(%lu)=%lu\n\n", n, z);
    }

    x=0,y=1,z=0;
    for(i=2; z<= ULONG_MAX/2;i++)
    {
        z=x+y;
        x=y;
        y=z;
        mx++;
        printf("F(%lu)=%lu;",mx,z);
    }

    printf("\n\nMaximum of ULONG:%lu", ULONG_MAX);
    printf("\nF(%lu)=F(%lu)+F(%lu)", mx+1,mx,mx-1);
    printf("\nF(%lu)>%lu\n", mx+1, ULONG_MAX);
    printf("Max n = %lu\n", mx);
    return 0;
}
