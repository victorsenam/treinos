#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef long long ll;
const int P = 60;
bool comp[P];
num primes[P], sol[P];
int ps, ss;
inline num getnum()
{
    char c = ' ';num n = 0;
    while(isspace(c=getchar_unlocked()));
    n = c - 0x30;
    while(isdigit(c=getchar_unlocked()))
        n = (n<<3) + (n<<1) + c - 0x30;
    return n;
}
num fexp(num a, num e, num m)
{
    num t = 1;
    while(e)
    {
        if(e&1) t = (ll(t)*ll(a))%m;
        a = (ll(a)*ll(a))%m;
        e >>= 1;
    }
    return t;
}
bool prime(num n)
{
    if(n%2 == 0) return n==2;
    if(n%3 == 0) return n==3;
    num e, s, a, x;
    e = 8*sizeof(num) - 1 - __builtin_clz((n-1)&-(n-1));
    s = (n-1)>>e;
    for(int i=0;i<10;i++)
    {
        a=rand();a %= n;
        if(a < 2) { i--; continue; }
        if((x = fexp(a,s,n)) == 1) continue;
        for(int r=0;r<e && x != n-1 && x != 1; r++)
            x = (ll(x)*ll(x))%n;
        if(x != n-1) return false;
    }
    return true;
}
inline num f(num x, num n)
{ return ((ll(x)*ll(x))%n + 1)%n; }
num gcd(num a, num b)
{ return b ? gcd(b,a%b) : a; }
num pollard(num n)
{
    if(!(n&1)) return 2;
    num x, y, d = 1;
    x=rand();x%=n;
    y = x;
    while(d == 1)
    {
        x = f(x,n);
        y = f(f(y,n),n);
        if(x>y)  d = gcd(x-y,n);
        else     d = gcd(y-x,n);
    }
    return d;
}
num factor(num n)
{
    num ans = n;
    while(ans == n)
        ans = pollard(n);
    return ans;
}
num remove_factor(num &m, num p)
{
    num loc = 1;
    sol[ss++] = p;
    while(m%p == 0)
    {
        loc++;
        m /= p;
    }
    return loc;
}

num n;
int main()
{
    srand(time(NULL));
    for(num p=2;p<P;p++)
        if(!comp[p])
        {
            primes[ps++] = p;
            if(p*p*p*p > num(1e7)) break;
            for(num q=p*p;q<P;q+=p)
                comp[q] = 1;
        }
    while(n = getnum())
    {
        ss = 0;
        num m = n, ans = 1;
        for(int i=0;i<ps;i++)
            if(m%primes[i] == 0)
                ans *= remove_factor(m, primes[i]);
        while(m > 1)
        {
            if(prime(m))
                ans *= remove_factor(m, m);
            else
            {
                num d = factor(m);
                ans *= remove_factor(m, min(d,m/d));
            }
        }
        m = n;
        printf("%d =", m);
        sort(sol, sol+ss);
        for(int i=0;i<ss;i++)
        {
            while(m%sol[i] == 0)
            {
                printf(" %d", sol[i]);
                m /= sol[i];
                if(m > 1) printf(" *");
            }
        }
        ans += 1;
        ans >>= 1;
        printf("\nWith %d marbles, %d different rectangles can be constructed.\n", n, ans);
    }
}

