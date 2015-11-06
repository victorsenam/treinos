#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 1e5 + 7;
const int ME = 1.5e5 + 7;

template<typename T> T& getnum(T& t)
{
    char c; T s = 1;
    while(isspace(c=getchar()));
    if(c=='-') s = -1, c=getchar();
    t = c-'0';
    while(isdigit(c=getchar())) t = (t<<3)+(t<<1)+c-'0';
    return t *= s;
}
template<typename T,typename... Ts> T& getnum(T& t, Ts&... rest)
{  getnum(t); getnum(rest...);  }

int n, m, p, ans, vs;
int hd[MV], match[MV], curr[MV], dist[MV], q[MV];
int to[ME], nx[ME], es;

int bfs()
{
    fill(dist,dist+vs,-1);
    int qf = 0, qb = 0, found = 0;
    for(node u=0;u<n;u++)
        if( match[u] == u )
            q[qb++] = u, dist[u] = 0;
    while(qf<qb)
    {
        node u = q[qf++];
        curr[u] = hd[u];
        for(edge e=hd[u];e!=-1;e=nx[e])
            if( match[to[e]] != to[e] && dist[match[to[e]]] == -1 )
            {
                dist[match[to[e]]] = dist[u] + 1;
                q[qb++] = match[to[e]];
            }
            else
                found |= match[to[e]] == to[e];
    }
    return found;
}

int dfs(node u)
{
    for(edge &e=curr[u];e!=-1;e=nx[e])
        if( match[to[e]] == to[e] || (dist[match[to[e]]] == dist[u] + 1 && dfs(match[to[e]])) )
        {
            match[u] = to[e];
            match[to[e]] = u;
            return 1;
        }
    return 0;
}

int main()
{
    getnum(n,m,p);
    vs = n + m;
    fill(hd,hd+vs,-1);
    while(p--)
    {
        node u, v; getnum(u)--; getnum(v)--;
        to[es] = n+v; nx[es] = hd[u]; hd[u] = es++;
    }
    for(node u=0;u<vs;u++) match[u] = u;
    while(bfs())
        while(42)
        {
            int aux = ans;
            for(node u=0;u<n;u++)
                ans += (match[u] == u && dfs(u));
            if( aux == ans ) break;
        }
    printf("%d\n", ans);
}

