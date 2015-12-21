#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int MP = 1001;
num x[MP], y[MP], r[MP], nans[MP], dans[MP];
int s[MP], n;

inline num gcd(num a, num b)
{ return b ? gcd(b,a%b) : a; }

inline bool touch(int i, int j)
{
    num d = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]),
        a = r[i] + r[j];
    return a*a == d;
}

void dfs(node u, num nans, num dans, int s)
{
    ::nans[u] = nans;
    ::dans[u] = dans;
    ::s[u] = s;
    for(node v=0;v<n;v++)
        if(touch(u,v) && !::s[v])
        {
            num tnans = nans*r[u],
                tdans = dans*r[v],
                div = gcd(tnans, tdans);
            if(s>0) dfs(v, tnans/div, tdans/div, -1);
            else    dfs(v, tnans/div, tdans/div,  1);
        }
}

int t;
int main()
{
    scanf(" %d", &t);
    while(t--)
    {
        memset(s, 0, sizeof s);
        scanf(" %d", &n);
        for(int i=0;i<n;i++)
            scanf(" %lld%lld%lld", x+i, y+i, r+i);
        dfs(0, 1, 1, 1);
        for(int i=0;i<n;i++)
            if(s[i])
            {
                printf("%lld", nans[i]);
                if(dans[i] != 1) printf("/%lld", dans[i]);
                if(s[i] > 0) printf(" clockwise\n");
                else printf(" counterclockwise\n");
            }
            else printf("not moving\n");
    }
}
