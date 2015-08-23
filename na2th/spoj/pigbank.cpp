#include<bits/stdc++.h>
#define oo 1000000000
#define MC 501
#define MW 10001
using namespace std;
typedef int num;
int t;
num coins[MC], weight[MC], val[MC], mem[MC][MW];
num n, pigWeight;

num solve( int p, num aval )
{
    if( p > n ) return oo;
    if( mem[p][aval] == -1 )
    {
        if( aval == 0 )
            mem[p][aval] = 0;
        else
        {
            mem[p][aval] = solve(p+1, aval);
            if( aval >= weight[p] )
                mem[p][aval] = min( mem[p][aval], val[p] + solve(p, aval-weight[p]) );
        }
    }
    return mem[p][aval];
}

int main()
{
    scanf("%d", &t);
    while( t-- > 0 )
    {
        num e, f;
        scanf("%d %d", &e, &f);
        scanf("%d", &n);

        memset(mem, -1, sizeof mem);
        memset(val, 0, sizeof val);
        memset(weight, 0, sizeof weight);
        for( int i = 0; i < n; i++ )
            scanf("%d %d",val+i, weight+i);
        num ans = solve(0, f-e);
        if( ans == oo )
            printf("This is impossible.\n");
        else
            printf("The minimum amount of money in the piggy-bank is %d.\n", ans);
    }
}

