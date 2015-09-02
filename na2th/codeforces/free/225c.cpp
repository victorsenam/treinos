#include<bits/stdc++.h>
#define MV 200003
#define ME 400003
typedef int num;
typedef int node;
typedef int edge;
num head[MV], tree[2][MV], parity[MV],
    val[MV], ini[MV], fim[MV];
num to[ME], next[ME], es;
num n, m, tmp;
using namespace std;

void dfs(node s, num p)
{
    parity[s] = p;
    ini[s] = tmp++;
    for(edge e=head[s]; e>=0 ; e = next[e])
        if( ini[to[e]] == 0 )
            dfs(to[e], p^1);
    fim[s] = tmp;
}

void insert(int t, int p, num val)
{
    for(; p>0; p-=(p&-p))
        tree[t][p] += val;
}

num count(int t, int p)
{
    num ans=0;
    for(; p<=n;p+=(p&-p))
        ans += tree[t][p];
    return ans;
}

int main()
{
    memset(head, -1, sizeof head); es=0;
    scanf("%d %d", &n, &m);
    for(int i=1;i<n+1;i++)
        scanf("%d", val+i);
    for(int i=0;i<n-1;i++)
    {
        num u,v; scanf("%d %d", &u, &v);
        to[es] = v; next[es] = head[u]; head[u] = es++;
        to[es] = u; next[es] = head[v]; head[v] = es++;
    }
    tmp=1;
    dfs(1,0);
    while(m--)
    {
        num q, x, v;
        scanf("%d %d", &q, &x);
        if( q == 2 )
            printf("%d\n", val[x] + count(parity[x], ini[x]));
        else
        {
            scanf("%d", &v);
            insert(parity[x], fim[x]-1,  v);
            insert(parity[x], ini[x]-1, -v);

            insert(parity[x]^1, fim[x]-1, -v);
            insert(parity[x]^1, ini[x]-1,  v);
        }
    }
}
