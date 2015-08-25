#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const int MP = 100004;
num n, m, e, d, c, phi, aux;
int primes[MP], ps;
char comp[MP];

num mod( num x, num y )
{ return (x%y + y)%y; }

num tot( num n )
{
    num ans = n, aux = n;
    for(int i=0;i<ps;i++)
        if( aux%primes[i] == 0 )
        {
            while( aux%primes[i] == 0 )
                aux /= primes[i];
            ans = ans/primes[i]*(primes[i]-1);
        }
    return ans;
}

num euclid(num a, num & x, num b, num & y)
{
    num d, ix, iy;
    if( a%b == 0 )
    {
        x = 0ll;
        y = 1ll;
        return b;
    }
    d = euclid(b,ix,a%b,iy);
    x = iy;
    y = ix - (a/b)*iy;
    return d;
}

num fexp( num a, int e )
{
    num t = 1;
    while(e)
    {
        if(e%2) t = mod(t*a, n);
        a  = mod(a*a,n);
        e /= 2;
    }
    return t;
}

int main()
{
    comp[0] = comp[1] = 1;
    for(int i=2;i<MP;i++)
        if( !comp[i] )
        {
            primes[ps++] = i;
            for(int j=2*i;j<MP;j+=i)
                comp[j] = 1;
        }

    scanf("%lld %lld %lld", &n, &e, &c);
    phi = tot(n);
    euclid(e,d,phi,aux);
    d = (d%phi + phi)%phi;
    printf("%lld\n", mod(fexp(c,d),n) );
}
