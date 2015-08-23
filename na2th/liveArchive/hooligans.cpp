#include<bits/stdc++.h>
const int MV = 1600;
const int ME = 5000;

typedef int num;
typedef int edge;
typedef int node;
using namespace std;

int head[MV], dist[MV], Q[MV], curr[MV], vs;
int to[ME], prox[ME], es;
num flow[ME], cap[ME];
num n,m,g,mP,R;

void add(node u, node v, num cuv, num cvu)
{
    to[es] = v; flow[es] = 0; cap[es] = cuv;
    prox[es] = head[u]; head[u] = es++;
    to[es] = u; flow[es] = 0; cap[es] = cvu;
    prox[es] = head[v]; head[v] = es++;
}

void bfs( node src )
{
    int qb=0, qf=0;
    fill(dist, dist+vs, -1);
    dist[src] = 0;
    Q[qb++] = src;
    while( qf < qb )
    {
        node u = Q[qf++];
        for( edge e = head[u]; e >= 0; e = prox[e] )
            if( cap[e] > flow[e] && dist[to[e]] == -1 )
            {
                dist[to[e]] = dist[u] + 1;
                Q[qb++] = to[e];
            }
    }
}

num dfs( node u, node g, num af )
{
    num ans = 0;
    if( u == g ) return af;
    for( edge &e = curr[u]; e >= 0; e = prox[e] )
        if( dist[to[e]] == dist[u] + 1 &&
            cap[e] > flow[e] &&
            (ans=dfs(to[e],g,min(af,cap[e]-flow[e]))) > 0)
        {
            flow[e] += ans;
            flow[e^1] -= ans;
            return ans;
        }
    return 0;
}

num maxFlow(node src, node snk)
{
    num ans = 0;
    for( bfs(src); dist[snk] != -1; bfs(src) )
    {
        for(int v=0;v<vs;v++) curr[v] = head[v];
        while(42)
        {
            num nf = dfs( src, snk, INT_MAX );
            if( nf > 0 ) ans += nf;
            else break;
        }
    }
    return ans;
}
int main()
{
    while( scanf("%d %d %d", &n, &m, &g) != EOF && n )
    {
        memset(head, -1, sizeof head); es=0;
        vs = n*n-n+3;
        mP = 2*m*(n-1);
        R  = 0;
        for(int i=1;i<n;i++)
            dist[i] = 0;
        for(int i=1;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                R += 2*m;
                dist[i*n + j] = 2*m;
            }

        while( g-- )
        {
            node u, v; char st;
            scanf("%d %c %d", &u, &st, &v);
            if( u==0 || v==0 )
            {
                if( st == '=' )
                {
                    mP--;
                    dist[max(u,v)]++;
                }
                else if( u == 0 )
                {
                    mP -= 2;
                    dist[max(u,v)] += 2;
                }
            }
            else
            {
                num match = min(u,v)*n + max(u,v);
                R -= 2;
                dist[match] -= 2;
                if( st == '=' )
                {
                    dist[u]++;
                    dist[v]++;
                }
                else
                    dist[v] += 2;
            }
        }
        for(int i=1;i<n;i++)
            add(i,0,mP-dist[i]-1,0);
        for(int i=1;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                add(n*n-n+1, i*n+j, dist[i*n+j], 0);
                add(i*n+j, i, 2*m, 0);
                add(i*n+j, j, 2*m, 0);
            }
        if( maxFlow(n*n-n+1, 0) == R )
            printf("Y\n");
        else
            printf("N\n");
    }
}
