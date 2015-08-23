#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const int MT = 102;
const int MOD = 10001;
num a, b, x[MT], poss[MOD];
int t, ps;

inline num mod(num x)
{ return (x%MOD + MOD)%MOD; }

int main()
{
    scanf("%d", &t);
    for(int i=0;i<t;i++)
        scanf("%lld", x+i);

    if( t == 1 )
    {
        printf("%lld\n", x[0]);
        return 0;
    }

    if( t == 2 )
    {
        for(int i=0;i<t;i++)
            printf("%lld\n", x[1]);
        return 0;
    }

    ps = 0;
    for(a=0;a<MOD;a++)
        if( mod(x[2]-x[1]) == mod(a*a*(x[1]-x[0])) )
            poss[ps++] = a;

    for(int i=0;i<ps;i++)
    {
        a = poss[i];
        for(b=0;b<MOD;b++)
        {
            bool ok = true;
            for(int j=0;ok && j<t-1;j++)
                ok &= (x[j+1] == mod(a*a*x[j] + a*b + b));
            if(ok)
            {
                i = ps;
                break;
            }
        }
    }
    for(int i=0;i<t;i++)
        printf("%lld\n", mod(a*x[i]+b));
}
