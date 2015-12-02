#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const num MOD = 1e9+7;

inline num mod(num x)
{ return x%MOD; }

num p, k, o, ans;

inline num fexp(num a, num e)
{
    num t = 1;
    while(e)
    {
        if(e&1) t = mod(t*a);
        a = mod(a*a);
        e>>=1;
    }
    return t;
}

int main()
{
    cin >> p >> k;
    if( k == num(0) )
    {
        cout << fexp(p,p-1) << endl;
        return 0;
    }

    num aux = k;
    o = num(1);
    while(aux != 1)
    {
        o++;
        aux = (k*aux)%p;
    }
    cout << fexp(p,p/o) << endl;
}
