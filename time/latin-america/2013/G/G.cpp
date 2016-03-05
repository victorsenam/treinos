#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int G = 150000;

int ans[N], as;
int h[N], v[N];
int i, u, d, n, hm;

int main()
{
    while(scanf(" %d", &n) != EOF)
    {
        as = 0;
        for(i=0;i<n;i++) scanf(" %d", h+i);
        memset(v, 0, sizeof v);
        u = d = 0;
        for(i=1;i<n-1;i++)
        {
            if(h[i] > u) u = d = h[i];
            else d = min(v[i]=d, h[i]);
        }
        u = d = 0;
        for(i=n-1;i>=0;--i)
        {
            if(h[i] > u) u = d = h[i];
            else v[i] = max(v[i], d), d = min(d, h[i]);
        }
        for(i=1;i<n-1;i++) if(h[i]-v[i] >= G && h[i] > max(h[i-1],h[i+1])) ans[as++] = i+1;
        for(i=0;i<as;i++) printf("%d%c", ans[i], " \n"[i+1==as]);
    }
}
