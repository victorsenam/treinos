#include<bits/stdc++.h>
#define MAX 1002
using namespace std;
typedef int num;
const num MOD = 1000000007;
num k, c[MAX], tot, ans;

num inv( num a )
{
    num t = 1, r = MOD-2;
    while(r)
    {
        if(r&1) t = (1ull*t*a)%MOD;
        a = (1ull*a*a)%MOD;
        r>>=1;
    }
    return t;
}

num choose( num n, num k )
{
    if( k == 0 ) return 1;
    num up = 1, down = 1;
    for( int i = 1; i < k; i++ )
    {
        up   = (1ull*up*(n-i))%MOD;
        down = (1ull*down*i)%MOD;
    }
    down = (1ull*k*down)%MOD;
    up   = (1ull*n*up)%MOD;
    return (1ull*up*inv(down))%MOD;
}

int main()
{
    scanf("%d", &k);
    for( int i = 0; i < k; i++ )
        scanf("%d", c+i);
    ans = 1;
    for( int i = 0; i < k; i++ )
    {
        tot += c[i];
        ans = (1ull*ans*choose(tot-1,c[i]-1))%MOD;
    }
    printf("%d\n", ans);
}
