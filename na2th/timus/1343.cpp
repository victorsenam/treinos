#include <bits/stdc++.h>
using namespace std;
typedef long long num;

num in, guess;

num multBy(num a,num b, num m)
{
    num ans = 0;
    while(b)
    {
        if(b&1) ans = (ans + a)%m;
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

bool miller_rabin(num n)
{
    if(n%2 == 0) return n == 2;
    if(n%3 == 0) return n == 3;
    num a, e, s, x;
    e = 8*sizeof(num) - 1 - __builtin_clzll( (n-1)&-(n-1) );
    s = (n-1)>>e;
    for(int i=0;i<20;i++)
    {
        a=rand();a<<=32;a^=rand();a%=n;
        if(a == 0) { --i; continue; }
        if((x=fexp(a,s,n)) == 1) continue;
        for(int r=0;r<e && x != n-1 && x != 1;r++)
            x = multBy(x,x,n);
        if(x != n-1) return false;
    }
    return true;
}

int n;
int main()
{
    srand(time(NULL));
    scanf(" %d %lld", &n, &in);
    while(42)
    {
        guess = in;
        for(int i=n;i<12;i++)
        {
            guess *= 10;
            guess += rand()%10;
        }
        if(miller_rabin(guess))
        {
            printf("%012lld\n", guess);
            break;
        }
    }
}
