#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef long long hsh;
const int MS   = 5000002;
const hsh MOD  = 1000000009;
const hsh base = 263ll;
char s[MS];
hsh in[MS], ni[MS], powers[MS];
int deg[MS], ans, n;

inline hsh mod( hsh x )
{ return x%MOD; }

int main()
{
    powers[0] = 1ll;
    for(int i=1;i<MS;i++)
        powers[i] = mod(base*powers[i-1]);

    scanf(" %s", s+1);
    n = strlen(s+1) + 1;
    for(int i=0;i<n;i++)
    {
        in[i] = mod(in[i-(i>0)] + s[i]*powers[i-1]);
        ni[i] = mod(ni[i-(i>0)]*base + s[i]);
    }

    for(int i=1;i<n;i++)
    {
        if( mod( in[i]*powers[n-i] ) == mod( ni[i]*powers[n-i] ) )
            deg[i] = 1 + deg[i/2];
        ans += deg[i];
    }
    printf("%d\n", ans);
}
