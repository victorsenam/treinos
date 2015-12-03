#include<bits/stdc++.h>
#define MV 60
#define ME 1403
typedef int num;
typedef int node;
typedef int edge;
using namespace std;

num head[MV], dist[MV], curr[MV], Q[MV], vs;
num to[ME], next[ME], f[ME], cap[ME], es;
num n, name[256];
char rname[256];

void add( node u, node v, num cuv, num cvu )
{
    //printf("%c - %c\n", rname[u], rname[v]);
    to[es] = v; f[es] = 0; cap[es] = cuv; next[es] = head[u]; head[u] = es++;
    to[es] = u; f[es] = 0; cap[es] = cvu; next[es] = head[v]; head[v] = es++;
}

void bfs( node src )
{
    int qf=0, qb=0;
    fill( dist, dist+vs, -1 );
    dist[src] = 0;
    Q[qb++] = src;
    while( qf < qb )
    {
        node u = Q[qf++];
        for( edge e = head[u]; e >=0; e = next[e] )
            if( cap[e] > f[e] && dist[to[e]] == -1 )
            {
                dist[to[e]] = dist[u] + 1;
                Q[qb++]     = to[e];
            }
    }
}

num dfs( node u, node g, num af )
{
    num ans;
    if( u == g ) return af;
    for( edge &e = curr[u]; e >= 0; e = next[e] )
        if( cap[e] > f[e] && dist[to[e]] == dist[u] + 1 && (ans=dfs(to[e],g,min(af,cap[e]-f[e]))) > 0 )
        {
            f[e] += ans;
            f[e^1] -= ans;
            return ans;
        }
    return 0;
}

num maxFlow( node src, node snk )
{
    num ans = 0;
    for( bfs(src); dist[snk] != -1; bfs(src) )
    {
        for( int i = 0; i < vs; i++ ) curr[i] = head[i];
        while( 42 )
        {
            num nf = dfs(src, snk, INT_MAX);
            if( nf > 0 ) ans += nf;
            else break;
        }
    }
    return ans;
}

int main()
{
    char a1, a2;
    num val;
    memset(head, -1, sizeof head); es = 0;
    memset(name, -1, sizeof name);
    scanf("%d ", &n);
    vs = 0;
    for( int i = 0; i < n; i++ )
    {
        scanf("%c %c %d ", &a1, &a2, &val);
        if( name[a1-'A'] == -1 )
        {
            name[a1-'A'] = vs;
            rname[vs++]  = a1; 
        }
        if( name[a2-'A'] == -1 )
        {
            name[a2-'A'] = vs;
            rname[vs++]  = a2;
        }
        add( name[a1-'A'], name[a2-'A'], val, val);
    }
    printf("%d\n", maxFlow(name['A'-'A'], name['Z'-'A']));
}
