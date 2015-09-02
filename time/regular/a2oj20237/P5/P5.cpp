#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const int MN = 15000;
const num MOD = 1000000007ll;
char comp[MN];
num primes[MN], powers[MN], ps, ans, aux, n, m, t;
int tc;

inline num mod( num x )
{ return (x%MOD + MOD)%MOD; }

int main()
{
    tc = 1;
    comp[0] = comp[1] = 1;
    for(int p=2;p<MN;p++)
        if( !comp[p] )
        {
            primes[ps++] = 1ll*p;
            for(int j=2*p;j<MN;j+=p)
                comp[j] = 1;
        }

    while( scanf("%lld %lld %lld", &n, &m, &t) != EOF && n )
    {
        for(int i=0;i<ps;i++) powers[i] = 0ll;
        for(int i=0;primes[i]<=n && i<ps;i++)
        {
            while( n%primes[i] == 0ll )
            {
                powers[i]++;
                n /= primes[i];
            }
        }

        ans = 1ll;
        for(int i=0;i<ps;i++)
            ans = mod(ans*(1ll + (powers[i]*m)/t ));

        aux = 1ll;
        for(int i=0;i<ps;i++)
            aux = mod(aux*(1ll + (powers[i]*m)/(t+1ll) ));

        printf("Case %d: %lld\n", tc++, mod(ans-aux));
    }
}
