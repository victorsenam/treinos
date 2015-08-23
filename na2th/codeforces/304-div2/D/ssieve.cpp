#include<bits/stdc++.h>
#define MAX 5000042
typedef int num;
using namespace std;

num accum[MAX], divs[MAX];

void slowSieve( int n )
{
    memset(divs, 0, sizeof divs);
    for( int i = 2; i <= n; i++ )
        if( divs[i] == 0 )
            for( long long p = i; p > 0 && p <= n; p *= i )
                for(int m = p; m <= n; m += p )
                    divs[m]++;
}

int main()
{
    num t, a, b, mAcc;

    slowSieve(5000010);
    accum[0] = accum[1] = 0;
    mAcc = 1;

    scanf("%d", &t);
    while( t-- > 0 )
    {
        scanf("%d %d", &a, &b);
        while( mAcc <= a )
        {
            accum[mAcc + 1] = divs[mAcc+1] + accum[mAcc];
            mAcc++;
        }
        printf("%d\n", accum[a] - accum[b]);
    }
}
