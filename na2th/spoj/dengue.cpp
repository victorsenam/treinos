#include<bits/stdc++.h>
#define MV 100
#define ME 200
typedef int num;
using namespace std;

num head[MV], dist[MV][MV], maxDist[MV], Q[MV], n;
num to[ME], next[ME], es; 
num ans, bestDist;

void bfs(int s)
{
    int qf = 0, qb = 0;
    for( int i = 0; i < n; i++ )
        dist[s][i] = -1;
    dist[s][s] = 1;
    maxDist[s] = 1;
    Q[qb++] = s;
    while( qf < qb )
    {
        num u = Q[qf++];
        maxDist[s] = max( dist[s][u], maxDist[s] );
        for( int e = head[u]; e >= 0; e = next[e] )
            if( dist[s][to[e]] == -1 )
            {
                dist[s][to[e]] = dist[s][u] + 1;
                Q[qb++]        = to[e];
            }
    }
}

int main()
{
    int tc = 1;
    while( scanf("%d", &n) != EOF && n )
    {
        printf("Teste %d\n", tc++);
        memset(head, -1, sizeof head);
        es = 0;
        for( int i = 0; i < n-1; i++ )
        {
            num x,y; scanf("%d %d", &x, &y);
            x--;y--;
            to[es] = y; next[es] = head[x]; head[x] = es++;
            to[es] = x; next[es] = head[y]; head[y] = es++;
        }

        ans = 0;
        bfs(0);
        for( int i = 1; i < n; i++ )
        {
            bfs(i);
            if( maxDist[i] < maxDist[ans] )
                ans = i;
        }
        printf("%d\n\n", ans+1);
    }
}
