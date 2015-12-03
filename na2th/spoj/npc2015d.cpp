#include <bits/stdc++.h>
using namespace std;
typedef long long num;

const num MOD = 1e9+7;
const int MN = 2e3;
num n, ans;

inline num fexp(num a, num e)
{
    num t = 1;
    while(e)
    {
        if(e&1) t = (t*a)%MOD;
        a = (a*a)%MOD;
        e>>=1;
    }
    return t;
}

int main()
{
    scanf(" %lld", &n);
    if(n > 3)
    {
        ans = fexp(num(3), n/num(3)-1);
        if(n%3 == 0) ans = (ans*num(3))%MOD;
        if(n%3 == 1) ans = (ans*num(4))%MOD;
        if(n%3 == 2) ans = (ans*num(6))%MOD;
    }
    else
        ans = n;
    printf("%lld\n", ans);
}
