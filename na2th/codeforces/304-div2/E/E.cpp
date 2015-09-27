#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
const int MN = 103;
const int oo = 1000000000;
num cap[MN][MN], a[MN], b[MN], f[MN], ans[MN][MN],
    dist[MN], anc[MN], q[MN], m, n, goal;

void bfs()
{
    int qb, qf;
    memset(dist, -1, sizeof dist);
    q[qb=qf=0] = 0; qb++;
    dist[0] = 0; anc[0] = 0; f[0] = oo;
    while( qf < qb )
    {
        node u = q[qf++];
        for(node v=1;v<n+2;v++)
            if( cap[u][v] > 0 && dist[v] == -1 )
            {
                anc[v] = u;
                f[v] = min( f[u], cap[u][v] );
                dist[v] = dist[u] + 1;
                q[qb++] = v;
            }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i=1;i<n+1;i++)
        scanf("%d", a+i);
    for(int i=1;i<n+1;i++)
        scanf("%d", b+i);
    for(int i=1;i<n+1;i++)
        ans[i][i] = a[i];
    for(int i=0;i<m;i++)
    {
        node u,v;
        scanf("%d %d", &u, &v);
        cap[u][v] = oo;
        cap[v][u] = oo;
    }
    for(int i=1;i<n+1;i++)
    {
        cap[i][n+1] = b[i];
        cap[0][i]   = a[i];
        goal += max(a[i]-b[i], b[i]-a[i]);
    }
    for(bfs();dist[n+1] != -1 ;bfs())
        for( node curr=n+1; anc[curr] != curr; curr = anc[curr] )
        {
            cap[anc[curr]][curr] -= f[n+1];
            cap[curr][anc[curr]] += f[n+1];
            ans[anc[curr]][curr] += f[n+1];
            ans[anc[curr]][anc[curr]] -= f[n+1];
            //ans[curr][curr] += f[n+1];
            goal -= f[n+1];
        }
    if( goal <= 0 )
    {
        printf("YES\n");
        for(int i=1;i<n+1;i++, printf("\n"))
            for(int j=1;j<n+1;j++)
                printf("%d ", ans[i][j]);
        printf("\n");
    }
    else
        printf("NO\n");
}
