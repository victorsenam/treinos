#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 550;
const int ME = (2*MV*MV);

int head[MV], curr[MV], dist[MV], Q[MV], vs;

int to[ME], next[ME], es;
num flow[ME], cap[ME];

num mP, x[MV], y[MV], radius[MV], w, p, goal;

void add(node u, node v, num cuv, num cvu)
{
    to[es] = v; flow[es] = 0; cap[es] = cuv;
    next[es] = head[u]; head[u] = es++;
    to[es] = u; flow[es] = 0; cap[es] = cvu;
    next[es] = head[v]; head[v] = es++;
}

void bfs(node src)
{
    int qf=0, qb=0;
    for(int i=0;i<vs;i++) dist[i] = -1;
    dist[src] = 0;
    Q[qb++] = src;
    while(qf<qb)
    {
        node u = Q[qf++];
        for(edge e=head[u];e>=0;e=next[e])
            if(cap[e]>flow[e] && dist[to[e]]==-1)
            {
                dist[to[e]] = dist[u] + 1;
                Q[qb++] = to[e];
            }
    }
}

num dfs(node u, node g, num af)
{
    num aux;
    if( u==g )return af;
    for(edge &e=curr[u];e>=0;e=next[e])
    {
        if( dist[to[e]] == dist[u] + 1 && 
            cap[e] > flow[e]           &&
            (aux=dfs(to[e],g,min(aux,cap[e]-flow[e])))>0)
        {
            flow[e] += aux;
            flow[e^1] -= aux;
            return aux;
        }
    }
    return 0;
}

num maxFlow(node src, node snk)
{
    num ans=0;
    for( bfs(src); dist[snk] != -1; bfs(src) )
    {
        printf("[%d]", dist[snk]);
        for(int v=0;v<vs;v++) curr[v] = head[v];
        while(42)
        {
            num nf=dfs(src,snk,INT_MAX);
            printf("{%d}", nf);
            if(nf>0) ans += nf;
            else break;
        }
        printf("\n");
    }
    return ans;
}

ull dist2(num ix, num iy, int p)
{ return (1ull*(ix-x[p])*(ix-x[p]) + 1ll*(iy-y[p])*(iy-y[p])); }

int main()
{
    int tc;
    scanf("%d", &tc);
    while( tc-- )
    {
        mP = 0; es = 0; vs = 0;
        memset(head, -1, sizeof head);
        scanf("%d %d", &w, &p);
        for(int i=0;i<w;i++)
            scanf("%d %d %d %d", x+i, y+i, dist+i, radius+i);
        vs = w;
        mP += dist[0];
        for(int i=0;i<p;i++)
        {
            num xi,yi,am;
            scanf("%d %d %d", &xi, &yi, &am);
            if( dist2(xi,yi,0) <= 1ull*radius[0]*radius[0] )
                mP += am;
            else
            {
                dist[vs] = am;
                for(int j=1;j<w;j++)
                if( dist2(xi,yi,j)<=1ull*radius[j]*radius[j])
                    add(vs, j, INT_MAX, 0);
                vs++;
            }
        }
        vs += 2;
        for(int i=1;i<w;i++)
            add(i,vs-1,mP-dist[i],0);
        for(int i=w;i<vs-2;i++)
            add(vs-2,i,dist[i],0);

        goal=0;
        for(edge e=head[vs-2];e>=0;e=next[e])
            goal += cap[e];
        if( w == 1 || maxFlow(vs-2,vs-1) == goal)
            printf("Suiting Success\n");
        else
            printf("Lonesome Willy\n");

    }
}
