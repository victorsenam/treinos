#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
inline num f(num x, num n)
{ return ((x*x)%n+1)%n; }
inline num gen()
{ num x = rand(); x <<= 32; return (x ^= rand()); }
num gcd(num a, num b)
{ return b ? gcd(b, a%b) : a; }
num pollard(num n)
{
    if(!(n&1)) return 2;
    num x, y,d = 1;
    y = x = gen();
    while(d == 1)
    {
        x = f(x,n);
        y = f(f(y,n),n);
        if(x>y)
             d = gcd(y-x,n);
        else d = gcd(y-x,n);
    }
    return d;
}
num factor(num n)
{
    num ans = n;
    for(int i=0;ans == n && i<50;i++)
        ans = pollard(n);
    return ans;
}
num euler(num n)
{
    num ans = 1;
    for(num p=2;p*p*p<=n;p++)
        if(!(n%p))
        {
            num q = 1;
            for(;!(n%p);n/=p)
                q *= p;
            q /= p;
            ans *= q*(p-1);
        }
    while(n>1)
    {
        num d = factor(n);
        if(d == n/d)
            ans *= d*(d-1), n = 1;
        else
        {
            ans *= d-1;
            n /= d;
        }
    }
    return ans;
}
num fexp(num a, num e, num m)
{
    num t = 1;
    while(e)
    {
        if(e&1)
            t = (t*a)%m;
        a = (a*a)%m;
        e >>= 1;
    }
    return t;
}
int main()
{
    srand(time(NULL));
    num e, n, c, d, m;
    int t;
    scanf(" %d", &t);
    while(t--)
    {
        scanf(" %llu%llu%llu", &e, &n, &c);
        num phi_n = euler(n);
        d = fexp(e, euler(phi_n)-1, phi_n);
        m = fexp(c, d, n);
        printf("%llu\n", m);
    }
}
