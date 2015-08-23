#include<bits/stdc++.h>
#define MV 53
#define ME 5002
using namespace std;
typedef int num;

num head[MV], dist[MV], Q[MV];
num to[ME], next[ME], es;
num c, e, l, p;

void bfs( num s )
{
    num qb,qf;
    for( int i = 0; i < c; i++ )
        dist[i] = INT_MAX;
    dist[s] = 0;
    Q[qb = qf = 0] = s; qb++;
    while( qf <= qb )
    {
        num u = Q[qf++];
        if( dist[u] > p ) break;
        for( int e = head[u]; e >= 0; e = next[e] )
            if( dist[to[e]] == INT_MAX )
            {
                dist[to[e]] = dist[u] + 1;
                Q[qb++]     = to[e];
            }
    }
}

int main()
{
    int tc = 1;
    while( scanf("%d %d %d %d", &c, &e, &l, &p) != EOF && c && e && l && p )
    {
        printf("Teste %d\n", tc++);
        memset(head, -1, sizeof head);
        es = 0; l--;
        for( int i = 0; i < e; i++ )
        {
            int u, v; scanf("%d %d", &u, &v);
            u--;v--;
            to[es] = v; next[es] = head[u]; head[u] = es++;
            to[es] = u; next[es] = head[v]; head[v] = es++;
        }
        bfs(l);
        for( int i = 0; i < c; i++ )
            if( i != l && dist[i] <= p )
                printf("%d ", i+1);
        printf("\n\n");
    }
}
