#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

template<typename T>T& getnum(T& t)
{
    char c; T s = 1;
    while(isspace(c=getchar()));
    if(c=='-') s=-1,c=getchar(); t=c-48;
    while(isdigit(c=getchar()))t=(t<<3)+(t<<1)+c-48;
    return t*=s;
}
template<typename T,typename...Ts> void getnum(T& t, Ts&...ts)
{ getnum(t); getnum(ts...); }

const int MN = 13;
const int MK = 100;
num sol[MN][MK], d, n, k;

int main()
{
    for(int i=1;i<MN;i++)
        sol[i][0] = num(1);

    for(int i=2;i<MN;i++)
        for(int q=1;q<MK;q++)
        {
            sol[i][q] = num(0);
            for(int j=0;j<min(i,q+1);j++)
                sol[i][q] += sol[i-1][q-j];
        }
    getnum(d);
    while(d--)
    {
        getnum(n,k);
        printf("%lld\n", sol[n][k]);
    }
}
