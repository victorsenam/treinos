#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int N = 107;
int n, s, f[N], t[N], p[N];
int curr, ans;

bool lvlLess(int i, int j)
{ return mp(-f[i], -t[i]) < mp(-f[j], -t[j]); }

int main()
{
    scanf(" %d%d", &n, &s);
    for(int i=0;i<n;i++)
    {
        scanf(" %d%d", f+i, t+i);
        p[i] = i;
    }
    sort(p, p+n, lvlLess);
    curr = s;
    for(int i=0;i<n;i++)
    {
        int k = p[i];
        ans = max(ans+curr-f[k], t[k]);
        curr = f[k];
    }
    printf("%d\n", ans+f[p[n-1]]);
}

