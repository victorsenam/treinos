#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = (1<<13)+3;
const int MN = 1002;
num sol[MN][MS], seen[MN][MS], tc, in[MN], acc[MN], n;

num solve(int i, int s)
{
    if( i == n )
        return (s == 0 && !(acc[n]&(acc[n]-1)) ) ||
               (2*s == acc[n] && !(s&(s-1)))       ||
               (s == acc[n] && !(s&(s-1))) ;

    if( seen[i][s] != tc )
    {
        int r = acc[i]-s;
        seen[i][s] = tc;
        sol[i][s] = 0;

        if( in[i] <= (r&(-r)) || r == 0 )
            sol[i][s] |= solve(i+1, s);

        if( in[i] <= (s&(-s)) || s == 0 )
            sol[i][s] |= solve(i+1, s+in[i]);

    }
    return sol[i][s];
}

int main()
{
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        acc[0] = as = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%d", in+i);
            acc[i+1] = acc[i] + in[i];
        }
        if(solve(0,0))
            while( as > 0 )
                printf("%c", ans[--as]);
        else
            printf("no");
        printf("\n");
    }
}
