#include <bits/stdc++.h>
using namespace std;
typedef long long num;

const int N = 1e5;
const int S = 320; 
int n, sqn;
num v[N], s[S], l[S];
void unlazy(int p)
{
    if(!l[p/sqn]) return;
    p -= p%sqn;
    do
    {
        v[p] += l[p/sqn];
        p++;
    }
    while(p < n && p%sqn);
    l[(p-1)/sqn] = 0;
}
void add(int l, int r, num x)
{
    int i;
    for(i=l;i<r && i%sqn;i++)
        v[i] += x, s[i/sqn] += x;
    for(;i/sqn < r/sqn;i+=sqn)
        s[i/sqn] += sqn*x, ::l[i/sqn] += x;
    for(;i<r;i++)
        v[i] += x, s[i/sqn] += x;
}
num query(int l, int r)
{
    int i;
    num ans = 0;
    unlazy(l); unlazy(r);
    for(i=l;i<r && i%sqn;i++)
        ans += v[i];
    for(;i/sqn < r/sqn;i+=sqn)
        ans += s[i/sqn];
    for(;i<r;i++)
        ans += v[i];
    return ans;
}

int c, t;
int main()
{
    scanf(" %d", &t);
    while(t--)
    {
        memset(v, 0, sizeof v);
        memset(s, 0, sizeof s);
        memset(l, 0, sizeof l);
        scanf(" %d%d", &n, &c);
        sqn = .5 + sqrt(n);
        while(c--)
        {
            int cmd, lo, hi;
            scanf(" %d%d%d", &cmd, &lo, &hi);
            lo--;
            if(cmd == 1) printf("%lld\n", query(lo, hi));
            else
            {
                num x; scanf(" %lld", &x);
                add(lo, hi, x);
            }
        }
    }
}
