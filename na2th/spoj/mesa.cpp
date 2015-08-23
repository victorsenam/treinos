#include<bits/stdc++.h>
#define MV 100
#define ME (2*50*99)
using namespace std;
typedef int num;

num head[MV], seen[MV], n;
num to[ME], next[ME], es, m;

bool dfs( int s, int label )
{
    bool conf = false;// Se achou conflito
    seen[s] = label;
    for( int e = head[s]; !conf && e >= 0 ; e = next[e] )
        if( seen[to[e]] == -1 )
            conf = dfs(to[e], label^1 );
        else
            conf = (label == seen[to[e]]);

    return conf;
}

int main()
{
    int tc = 1;
    while ( scanf("%d %d", &n, &m) != EOF )
    {
        printf("Instancia %d\n", tc++);
        memset(head, -1, sizeof head);
        memset(seen, -1, sizeof seen);
        es = 0;
        for( int i = 0; i < m; i++ )
        {
            int u, v; scanf("%d %d", &u, &v);
            to[es] = v; next[es] = head[u]; head[u] = es++;
            to[es] = u; next[es] = head[v]; head[v] = es++;
        }
        bool found = false;
        for( int i = 0; !found && i < n; i++ )
            if( seen[i] == -1 )
                found = dfs(i, 0);

        if( found )
            printf("nao\n");
        else
            printf("sim\n");
        printf("\n");
    }
}
