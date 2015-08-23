#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 10001;
const int ME = 100002;

int head[MV], pre[MV], pos[MV], top[MV], prei, posi, vs;
int to[ME], next[ME], es;
int cyc, unq, m;

int dfs(node u)
{
    int ans = 0;
    pre[u] = prei++;
    for(edge e=head[u];!ans && e>=0;e=next[e])
        if( pre[to[e]] == -1 )
            cyc |= dfs(to[e]);
        else if( pos[to[e]] == -1 )
            cyc = 1;
    pos[u] = posi;
    top[posi++] = u;
    return ans;
}

int main()
{
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d %d", &vs, &m);
        es=0;
        for(node v=0;v<vs;v++)
            pre[v] = pos[v] = head[v] = -1;
        while(m--)
        {
            node u,v; scanf("%d %d", &u, &v);
            u--;v--; to[es] = v;
            next[es] = head[u]; head[u] = es++;
        }
        cyc = 0;
        prei = posi = 0;
        for(node v=0;!cyc && v<vs;v++)
            if( pre[v] == -1 )
                cyc |= dfs(v);
        unq = 1;
        for(int i=posi-1;!cyc && unq && i>0;i--)
        {
            int found=0;
            for(edge e=head[top[i]];!found && e>=0;e=next[e])
                found |= (to[e] == top[i-1]);
            unq &= found;
        }
        if( cyc )
            printf("recheck hints\n");
        else if( !unq )
            printf("missing hints\n");
        else
        {
            while( posi > 0 )
                printf("%d ", top[--posi]+1);
            printf("\n");
        }

    }
}

