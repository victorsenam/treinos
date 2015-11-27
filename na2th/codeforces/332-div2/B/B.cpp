#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

const int MOD = 1e9+7;
struct mod
{
    num x;
    mod () : x(0) {}
    mod (num a) : x(a) {}
    mod operator+(mod b) { return (1ll*x+1ll*b.x)%MOD; }
    mod operator*(mod b) { return (1ll*x*1ll*b.x)%MOD; }
};

const int MN = 1e5+7;
int f[MN], inv[MN], b[MN], a[MN], m, n;
int amb;

int main()
{
    scanf(" %d%d", &n, &m);
    for(int i=1;i<n+1;i++)
        scanf(" %d", f+i);

    for(int i=1;i<n+1;i++)
    {
        if (inv[f[i]] == 0)
            inv[f[i]] = i;
        else
            inv[f[i]] = -1;
    }
    amb = 0;
    for(int i=1;i<m+1;i++)
    {
        scanf(" %d", b+i);
        if( inv[b[i]] == -1 )
            amb |= 1;
        else if( inv[b[i]] == 0 )
        {
            printf("Impossible\n");
            return 0;
        }
        else
            a[i] = inv[b[i]];
    }

    if(amb)
        printf("Ambiguity\n");
    else
    {
        printf("Possible\n");
        for(int i=1;i<m+1;i++)
            printf("%d ", a[i]);
    }
}
