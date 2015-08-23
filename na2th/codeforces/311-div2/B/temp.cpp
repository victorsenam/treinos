#include <bits/stdc++.h>
#define MAX 200003
#define eps 1e-9
using namespace std;
typedef int num;
num n;
double a[MAX], w;

int main()
{
    scanf("%d %lf", &n, &w);
    for( int i = 0; i < 2*n; i++ )
        scanf("%lf", a+i);
    sort(a,a+2*n);

    double lo = 0.0,
           hi = w;

    while( fabs(hi-lo) > eps )
    {
        double mid = 0.5*(hi+lo),
               val = mid/(3*n);
        bool coube = true;
        for( int i = 0; coube && i < n; i++ )
            coube = ( a[i] > val );

        for( int i = n; coube && i < 2*n; i++ )
            coube = ( a[i] > 2*val );

        if( coube )
            lo = mid;
        else
            hi = mid;
    }
    printf("%lf\n", hi);
}
