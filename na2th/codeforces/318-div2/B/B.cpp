#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 4002;
const int ME = 2*MV;

int head[MV], deg[MV], n;
char know[MV][MV];
int to[ME], next[ME], from[ME], es;
int best, local, m;

int main()
{
    memset(head, -1, sizeof head);
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++)
    {
        node a,b;
        scanf("%d %d", &a, &b); a--; b--;

        deg[a]++;
        deg[b]++;

        to[es] = a; from[es] = b;
        next[es] = head[b]; head[b] = es++;

        to[es] = b; from[es] = a;
        next[es] = head[a]; head[a] = es++;

        know[a][b] = know[b][a] = 1;
    }

    if( es == 0 )
    {
        printf("%d\n", -1);
        return 0;
    }

    best = INT_MAX;
    for(int i=0;i<es;i+=2)
    {
        node u = from[i],
             v = to[i];
        for(edge e=head[u];e>=0;e=next[e])
            if( know[to[e]][v] )
                best = min(best, deg[u] + deg[v] + deg[to[e]] - 6);
    }

    if( best < INT_MAX )
        printf("%d\n", best);
    else
        printf("%d\n", -1);
}
