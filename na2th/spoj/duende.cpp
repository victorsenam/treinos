#include<bits/stdc++.h>
using namespace std;
typedef int num;

num n, m, Q[100];
num in[10][10], dist[100], anc[100];

num dx[4] = {-1,  1,  0,  0},
    dy[4] = { 0,  0, -1,  1};

num bfs( int s )
{
    int qf = 0, qb = 0;
    memset(dist, -1, sizeof dist);
    memset(anc , -1, sizeof anc );
    anc[s]  = s;
    dist[s] = 0;
    Q[qb++] = s;
    while( qf < qb )
    {
        num u = Q[qf++];
        if( in[u/m][u%m] == 0 )
            return dist[u];
        for( int i = 0; i < 4; i++ )
        {
            if( u%m + dx[i] >= m || u%m + dx[i] < 0 ||
                u/m + dy[i] >= n || u/m + dy[i] < 0   )
                continue;
            num v = u + dy[i]*m + dx[i];
            if( in[v/m][v%m] != 2 && dist[v] == -1 )
            {
                anc[v]  = u;
                dist[v] = dist[u] + 1;
                Q[qb++] = v;
            }
        }
    }
    return INT_MAX;
}

int main()
{
    int s;
    scanf("%d %d", &n ,&m);
    for( int i = 0; i < n*m; i++ )
    {
        scanf(" %d", &in[i/m][i%m] );
        if( in[i/m][i%m] == 3 )
            s = i;
    }
    printf("%d\n", bfs(s) );
}
