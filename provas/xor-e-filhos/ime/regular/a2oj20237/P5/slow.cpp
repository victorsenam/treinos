#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const num MOD = 100000007;

num fexp(num a, num e)
{
    num t = 1ll;
    while(e)
    {
        if(e%2ll == 1ll) t = (t*a)%MOD;
        a = (a*a)%MOD;
        e /= 2ll;
    }
    return t;
}

int main()
{
    num n, m, t, ans, aux;
    while( scanf("%lld %lld %lld", &n, &m, &t) != EOF )
    {
        ans = 0ll;
        aux = fexp(n,m);
        for(num b=1ll;b<=n;b++)
            ans += ( aux%fexp(b,t) == 0ll && aux%fexp(b,t+1ll) != 0ll );
        printf("%lld\n", ans);
    }
}
