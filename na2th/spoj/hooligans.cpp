#include<bits/stdc++.h>
#define MV 1600 
#define ME (2*MV*MV)
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

// Coisas da entrada
num head[MV], dist[MV], Q[MV], curr[MV], vs;
num to[ME], next[ME], flow[ME], cap[ME], es;
num n, m, g, mP, R, ok;

void add(node u, node v, num cuv, num cvu)
{
    // Adiciona aresta de u->v com capacidade cuv
    to[es] = v; flow[es] = 0; cap[es] = cuv;
    next[es] = head[u]; head[u] = es++;

    // Adiciona aresta de v->u com capacidade cvu
    to[es] = u; flow[es] = 0; cap[es] = cvu;
    next[es] = head[v]; head[v] = es++;
}

// BFS no residual. Não tem muito o que explicar.
void bfs(node s)
{
    int qf=0, qb=0;
    for(int i=0;i<vs;i++) dist[i] = INT_MAX;
    dist[s] = 0;
    Q[qb++] = s;
    while( qf < qb )
    {
        node u = Q[qf++];
        for(edge e = head[u]; e >= 0; e = next[e])
            if( cap[e] > flow[e] && dist[to[e]] == INT_MAX )
            {
                dist[to[e]] = dist[u] + 1;
                Q[qb++] = to[e];
            }
    }
}

num dfs(node s, node g, num af)
{
    if( s == g )
        return af;
    num aux;
    for(edge &e = curr[s]; e >= 0 ; e = next[e] )
        if( dist[to[e]] == dist[s] + 1 &&
            cap[e] > flow[e]           &&
            ( aux=dfs( to[e], g, min(af,cap[e]-flow[e]) ) )>0 )
        {
            flow[e]   += aux;
            flow[e^1] -= aux;
            return aux;
        }
    return 0;
}

num maxFlow(node s, node g)
{
    num ans=0;
    for( bfs(s); dist[g] < INT_MAX; bfs(s) )
    {
        for(int v=0; v < vs; v++ ) curr[v] = head[v];
        while( 42 )
        {
            num nf = dfs(s,g,INT_MAX);
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
        vs = n*n-n+2;
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
        ok = 1;
        for(int i=1;i<n;i++)
        {
            add(i,0,mP-dist[i]-1,0);
            ok &= ( mP-dist[i] > 0 );
        }
        for(int i=1;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                add(n*n-n+1, i*n+j, dist[i*n+j], 0);
                add(i*n+j, i, INT_MAX, 0);
                add(i*n+j, j, INT_MAX, 0);
            }
        if( ok && maxFlow(n*n-n+1, 0) == R )
            printf("Y\n");
        else
            printf("N\n");
    }
}
