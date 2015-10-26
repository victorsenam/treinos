#include <bits/stdc++.h>
using namespace std;
const int MN = 32009;
int fac[MN];
int t, e, n, c;

inline int euler(int x)
{
    int ans = x;
    for(int curr=x;curr>1;)
    {
        ans = ans/fac[curr]*(fac[curr]-1);
        for(int div=fac[curr]; !(curr%div); curr /= div);
    }
    return ans;
}

inline int fexp(int x, int e, int mod)
{
    int t = 1;
    while(e)
    {
        if(e&1) t = (t*x)%mod;
        x = (x*x)%mod;
        e >>= 1;
    }
    return (t+mod)%mod;
}

int main()
{
    for(int i=2;i<MN;i++)
        if( !fac[i] )
        {
            fac[i] = i;
            for(int j=i*i;j<MN;j+=i)
                fac[j] = i;
        }
    scanf(" %d", &t);
    while(t--)
    {
        scanf(" %d%d%d", &e, &n, &c);
        int phi  = euler(n);
        int phi2 = euler(phi);
        int d    = fexp(e, phi2-1, phi);
        printf("%d\n", fexp(c, d, n));
    }
}
