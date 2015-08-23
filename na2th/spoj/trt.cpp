#include<bits/stdc++.h>
#define MT 2002
using namespace std;
typedef unsigned long long num;
num val[MT], sol[MT][MT];
num n;

num solve( int l, int r )
{
    if( r >= n ) return INT_MIN;
    if( sol[l][r] == -1 )
    {
        num year = (num)(n-(r-l));
        if( l == r )
            sol[l][r] = year*val[l];
        else
            sol[l][r] = max( year*val[l] + solve(l+1,r),
                             year*val[r] + solve(l,r-1) );
    }
    return sol[l][r];
}

int main()
{
    scanf("%d", &n);
    memset( sol, -1, sizeof sol );
    memset( val, 0, sizeof val );
    for( int i = 0; i < n; i++ )
        scanf("%llu", val+i);
    printf("%llu\n", solve(0,n-1) );
}
