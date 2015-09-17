#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 1001;
const int ME = 2*100001;

int id[MV];
int from[ME], to[ME], w[ME], ord[ME], es;
int n, m, l, h, ans;

bool edgeLess(int i, int j)
{ return w[i] < w[j]; }
int find(int u)
{ return (id[u]<0) ? u : (id[u]=find(id[u])); }
int merge(int u, int v)
{
    if( (u=find(u)) == (v=find(v)) )
        return 0;
    if( id[v] > id[u]  ) swap(u,v);
    id[u] += id[v]; id[v] = u; return 1;
}

int main()
{
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d %d", &n, &m);
        memset(id, -1, sizeof id); es = 0;
        for(int i=0;i<m;i++)
        {
            node u,v; int c;
            scanf("%d %d %d", &u, &v, &c); u--; v--;
            to[es] = u; w[es] = c; from[es] = v; ord[es] = es++;
            to[es] = v; w[es] = c; from[es] = u; ord[es] = es++;
        }
    }
}
