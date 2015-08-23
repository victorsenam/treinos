#include<bits/stdc++.h>
#define MQ 16
using namespace std;
typedef int num;
num n, l, r, x, d[MQ];
num accum, minq, maxq;

int count( int p )
{
    num ans = 0, mmin, mmax;
    if( p == n )
        return ( l <= accum && accum <= r && accum > 0 && maxq - minq >= x ) ? 1 : 0;
    if( p == 0 )
    {
        minq = INT_MAX; maxq = INT_MIN; accum = 0;
    }

    // Guardo coisas
    mmin = minq; mmax = maxq;

    // Tento sem
    ans += count(p+1);

    // Tento com
    accum += d[p];
    minq  = min(minq, d[p]);
    maxq  = max(maxq, d[p]);
    ans += count(p+1);

    accum -= d[p];
    minq = mmin; maxq = mmax;
    return ans;
}

int main()
{
    scanf("%d %d %d %d", &n, &l, &r, &x);
    for( int i = 0; i < n; i++ )
        scanf("%d", d+i);
    printf("%d\n", count(0));
}
