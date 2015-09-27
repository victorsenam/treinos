#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
const int MN  = 100001;
const num MOD = 1000000009;
num n, a[MN], d;

num mdc(num a, num b)
{ return ( b == 0ull ) ? a : mdc(b, a%b); }

num mmc(num a, num b)
{ return (a/mdc(a,b)*b)%MOD; }

int main()
{
    cin >> n;
    for(num i=0ull;i<n;i++)
        cin >> a[i];
    d = 1ull;
    for(num i=0ull;i<n;i++)
        d = mmc(d,a[i]);

    bool ok = 1;
    for(num i=0ull;ok && i<n;i++)
    {
        a[i] = d/a[i];
        while( a[i]%2ull == 0ull )
            a[i] /= 2ull;
        while( a[i]%3ull == 0ull )
            a[i] /= 3ull;

        ok &= (a[i] == 1ull);
    }
    if(ok)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}
