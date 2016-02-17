#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define bi back_inserter
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;
const int N = 1e5;
const int M = 2e5;
int n, m;
int hd[N], last[N];
num spines[N], best[N], ans;
int to[M], nx[M], es;

int main()
{
    ios::sync_with_stdio(false);
    memset(hd, -1, sizeof hd);
    es = 0;
    cin >> n >> m;
    while(m--)
    {
        node u, v;
        cin >> u >> v; --u; --v;
        to[es] = v; nx[es] = hd[u]; hd[u] = es++;
        to[es] = u; nx[es] = hd[v]; hd[v] = es++;
        spines[u]++; spines[v]++;
    }
    for(node u=0;u<n;u++)
    {
        best[u] = 1;
        for(edge e=hd[u];e!=-1;e=nx[e])
            if(to[e] < u)
                best[u] = max(best[u], best[to[e]] + 1);
    }
    ans = 0;
    for(node u=0;u<n;u++)
        if(best[u]*spines[u] > ans)
            ans = best[u]*spines[u];
    cout << ans << endl;
}
