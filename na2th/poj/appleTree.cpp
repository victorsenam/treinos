#include<cstdio>
#include<cstring>
#include<algorithm>
#define MV 100010
#define ME 200010
typedef int num;
typedef int node;
typedef int edge;

num head[MV], ini[MV], fim[MV], tree[MV];
num to[ME], next[ME], es;
num label, n, m;

void insert(int p, num val)
{
    for(; p <= n; p += (p&-p))
        tree[p] += val;
}

num count(int p)
{
    num ans=0;
    for(; p>0; p-=(p&-p))
        ans += tree[p];
    return ans;
}

void dfs(node s)
{
    ini[s] = label++;
    for(edge e=head[s];e>=0;e=next[e])
        if(ini[to[e]] == -1)
            dfs(to[e]);
    fim[s] = label;
}

int main()
{
    scanf("%d", &n);
    memset(head,-1,sizeof head); es = 0;
    memset(ini,-1,sizeof ini);
    for(int i = 0; i < n-1; i++)
    {
        node u,v; scanf("%d %d", &u, &v);
        to[es] = v; next[es] = head[u]; head[u] = es++;
        to[es] = u; next[es] = head[v]; head[v] = es++;
    }
    label=1;dfs(1);
    for(int i=1;i<n+1;i++) tree[i] = (i&-i);
    //for(int i=1;i<n+1;i++) printf("%d [%d]\n", i, count(ini[i])-count(ini[i]-1));
    //for(int i=1;i<n+1;i++) printf("%d [%d,%d]\n", i, ini[i], fim[i]);
    scanf("%d", &m);
    while(m-->0)
    {
        char cmd; node u;
        scanf(" %c %d", &cmd, &u);
        //printf("%c-%d\n", cmd, u);
        if(cmd=='C')
        {
            if( count(ini[u]) == count(ini[u]-1) )
                insert(ini[u], 1);
            else
                insert(ini[u], -1);
        }
        else
            printf("%d\n", count(fim[u]-1) - count(ini[u]-1)); 
        //for(int i=1;i<n+1;i++) printf("%d [%d]\n", i, count(ini[i])-count(ini[i]-1));
    }
}
