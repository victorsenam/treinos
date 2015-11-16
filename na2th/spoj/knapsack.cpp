#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

template<typename T>T& getnum(T& t)
{
    char c; T s = 1;
    while(isspace(c=getchar()));
    if(c=='-') s=-1,c=getchar();
    t = c-48;
    while(isdigit(c=getchar())) t = (t<<3)+(t<<1)+c-48;
    return t*=s;
}
template<typename T,typename... Ts> void getnum(T& t, Ts&...ts)
{ getnum(t); getnum(ts...); }

const int MS = 2e3+1;
const int MN = 2e3;
num sol[MN][MS];
num w[MN], v[MN], n, s;

int main()
{
    getnum(s,n);
    for(int i=0;i<n;i++) getnum(w[i],v[i]);

    for(int s=0;s<::s+1;s++)
        sol[0][s] = v[0]*(w[0]<=s);
    for(int i=1;i<n;i++)
        for(int s=0;s<::s+1;s++)
        {
            sol[i][s] = sol[i-1][s];
            if(w[i] <= s)
                sol[i][s] = max(sol[i][s], sol[i-1][s-w[i]] + v[i]);
        }
    printf("%lld\n", sol[n-1][s]);
}
