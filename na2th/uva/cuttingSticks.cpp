#include<bits/stdc++.h>
#define MC 53
#define oo 1000000000
using namespace std;
typedef int num;
num cuts[MC], sol[MC][MC], n;

num solve( int l, int r )
{
    if( l > r ) return oo;
    if( sol[l][r] == -1 )
    {
        num aux;
        if( l + 1 == r )
            aux = cuts[l] - cuts[r];
        else
        {
            aux = oo;
            for( int i = l+1; i < r; i++ )
                aux = min( aux, solve(l,i) + solve(i,r) );
        }
        sol[l][r] = cuts[r] - cuts[l] + aux;
    }
    return sol[l][r];
}

int main()
{
    while( scanf(" %d", cuts) > 0 && cuts[0] > 0)
    {
        scanf("%d", &n);
        for( int i = 1; i < n + 1; i++)
            scanf("%d", cuts+i);
        cuts[n+1] = 0;
        swap( cuts[n+1], cuts[0] );
        memset( sol, -1,sizeof sol );
        printf("The minimum cutting is %d.\n", solve(0, n+1) );
    }
}
