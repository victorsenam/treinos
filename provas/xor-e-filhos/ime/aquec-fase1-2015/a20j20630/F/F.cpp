#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 2501;
const int ME = 2*10001;

int head[MV], rhad[MV], label[MV], sol[MV];
int to[ME], next[ME], es;
int n, m, l, ans;

void dfs(node u, int l)
{
    label[u] = l;
    for (edge e=rhad[u]; e>=0; e=next[e])
        if( label[to[e]] != l )
        {
            sol[to[e]]++;
            dfs(to[e], l);
        }
}

int main()
{
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        memset(head, -1, sizeof head);
        memset(rhad, -1, sizeof rhad);
        es = 0;
        scanf("%d %d", &n, &m);
        for(int i=0;i<m;i++)
        {
            node u,v; scanf("%d %d", &u, &v);
            u--;v--;
            to[es] = v; next[es] = head[u]; head[u] = es++;
            to[es] = u; next[es] = rhad[v]; rhad[v] = es++;
        }
        memset(label, -1, sizeof label);
        memset(sol, 0, sizeof sol);
        for(node v=0;v<n;v++)
            dfs(v,v);
        ans = 0;
        for(node v=0;v<n;v++)
            ans += sol[v];
        printf("%d\n", ans);
    }
}
