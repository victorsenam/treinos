#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long num;

num multBy(num a, num b, num m)
{
    if(b<a) return multBy(b,a,m);
    num ans = 0;
    while(b)
    {
        if(b&1) ans = (ans+a)%m;
        a = (a<<1)%m;
        b>>=1;
    }
    return ans;
}
num fexp(num a, num e, num m)
{
    num t = 1;
    while(e)
    {
        if(e&1) t = multBy(t,a,m);
        a = multBy(a,a,m);
        e>>=1;
    }
    return t;
}
bool fermat(num n)
{
    num a = rand(); a <<= 32; a ^= rand();
    return a%n == fexp(a%n,n,n);
}
bool prime(num n)
{
    num p = 2;
    for(;p<1000 && p*p<=n;p++)
        if(!(n%p)) return false;
    int ok = 1;
    for(int i=0;ok && i<50;i++)
        ok &= fermat(n);
    return ok;
}

int main()
{
    num n, ans = 1;
    srand(time(NULL));
    scanf("%llu", &n);
    num p = 2, loc;
    for(;p*p*p<=n;p++)
        if(!(n%p))
        {
            loc = 1;
            while(n%p == 0)
                loc++, n /= p;
            ans *= loc;
        }
    if(n > 1)
    {
        if(fermat(n))
            ans *= 2;
        else
        {
            num p = sqrt(n); p-=2;
            for(;p*p<n;p++);
            if(p*p==n) ans *= 3;
            else ans *= 4;
        }
    }
    cout << ans << endl;
}
