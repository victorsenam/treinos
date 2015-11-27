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
    while(isspace(c=getchar_unlocked()));
    if(c=='-') s = -1, c=getchar_unlocked(); t = c-48;
    while(isdigit(c=getchar_unlocked())) t = (t<<3)+(t<<1)+c-48;
    return t *= s;
}
template<typename T,typename... Ts> T& getnum(T& t, Ts&... rest)
{  getnum(t); getnum(rest...);  }

int n, m, p, ans, lst, mk, vs, qf, qb, found;
int hd[MV], match[MV], curr[MV], dist[MV], q[MV];
int to[ME], nx[ME], es;

int bfs()
{
    fill(dist,dist+vs,-1);
    qf = qb = found = 0;
    for(node u=0;u<n;u++)
        if( match[u] == u )
            q[qb++] = u, dist[u] = 0;
    if( (mk=qb) == 0 ) return 0;
    while(qf<qb)
    {
        node u = q[qf++];
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
    getnum(n);
    getnum(m);
    getnum(p);
    vs = n + m;
    for(node u=0;u<vs;u++)
        hd[u] = -1, match[u] = u;
    while(p--)
    {
        node u, v; getnum(u)--; getnum(v)--;
        to[es] = n+v; nx[es] = hd[u]; hd[u] = es++;
    }
    while(bfs())
    {
        lst = -1;
        memcpy(curr, hd, sizeof(int)*vs);
        while(ans != lst)
        {
            lst = ans;
            for(int i=0;i<mk;i++)
                ans += (match[q[i]] == q[i] && dfs(q[i]));
        }
    }
    printf("%d\n", ans);
}

