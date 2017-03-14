#include <bits/stdc++.h>
using namespace std;
typedef long long num;
const num MOD = 1000000007ll;
const int MD = 82;
const int MI = 11;
int p[MI];
int turn;
int vis[MI][MD];
num pot[MD], fact[MD], invf[MD], sol[MI][MD], ans;
int tc, sum;

inline num mod(num x)
{ return (x%MOD + MOD)%MOD; }

num inv( num x )
{
    num t=1ull, e = MOD-2ll;
    while(e)
    {
        if(e&1ll) t = mod(t*x);
        x = mod(x*x);
        e >>= 1ll;
    }
    return mod(t);
}

num solve(int i, int k)
{
    if(k==0) return 1ll;
    if(i==10) return 0ll;
    if( vis[i][k] != turn )
    {
        vis[i][k] = turn;
        sol[i][k] = 0ll;
        for(int j=0; j<min(p[i],k)+1; j++)
            sol[i][k] = mod(sol[i][k]+solve(i+1,k-j)*invf[j]);
    }
    return sol[i][k];
}

int main()
{
    pot[0] = 1ll;
    for(int i=1; i<MD; i++)
        pot[i] = mod(10ll*pot[i-1]);
    fact[0] = 1ll;
    for(num i=1ll;i<MD; i++)
        fact[i] = mod(i*fact[i-1ll]);
    for(num j=0ll; j<11ll;j++)
        invf[j] = inv(fact[j]);
    scanf("%d", &tc);
    while(tc--)
    {
        sum = 0;
        for(int i=1;i<10;i++)
        {
            scanf("%d", p+i);
            sum += p[i];
        }
        ans = 0ll;

        for(num i=1ll;i<10ll;i++)
        {
            if(p[i]==0) continue;
            p[i]--;
            turn++;
            for(int k=0; k<sum+1; k++)
            for(int j=0; j<k+1; j++)
                ans = mod(ans + i*pot[j]*mod(fact[k]*solve(1,k)));
            p[i]++;
        }
        printf("%lld\n", mod(ans));
    }
}
