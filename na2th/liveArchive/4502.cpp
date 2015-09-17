#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const int MOD = 100000007;
const int MN = 10001;
struct mod
{
    int x;
    mod () : x(0) {}
    mod (int a) : x(a) {}
    mod operator+(mod b) { return ((long long)x+(long long)b.x)%MOD; }
    mod operator-(mod b) { return ((long long)x+MOD-(long long)b.x)%MOD; }
    mod operator*(mod b) { return ((long long)x*(long long)b.x)%MOD; }
};
num n, m, t, aux, tc;
num primes[MN], powers[MN], ps;
char comp[MN];
mod ans[MN], a1, a2;

int main()
{
    for(int i=2;i<MN;i++)
        if( !comp[i] )
        {
            primes[ps++] = i;
            if( primes[ps-1] > 100000001 )
                break;
            for(int j=2*i;j<MN;j+=i)
                comp[j] = 1;
        }
    tc++;
    while( scanf("%lld %lld %lld", &n, &m, &t) != EOF && n )
    {
        memset(powers, 0, sizeof powers);

        aux = n;
        for(int i=0;i<ps;i++)
        {
            while( aux%primes[i] == 0 )
            {
                aux /= primes[i];
                powers[i] = powers[i] + 1;
            }
        }

        if( aux > 1 )
            powers[ps] = 1;

        a1 = 1;
        for(int i=0;i<ps+1;i++)
            a1 = a1*mod((powers[i]*m)/t+1ll);

        a2 = 1;
        for(int i=0;i<ps+1;i++)
            a2 = a2*mod((powers[i]*m)/(t+1ll)+1ll) ;

        printf("Case %lld: %lld\n",tc++, a1-a2);
    }
}
