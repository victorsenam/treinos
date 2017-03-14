#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MG = 501;
const int MV = 3*MG*MG;
const int ME = 4*MV + 2;
int b, w,n,m;
int tc;

char in[MG][MG];
int id[MG][MG];
int dx[4] = {1, -1, 0, 0},
    dy[4] = {0, 0, 1, -1};

inline bool inRange(int l, int x, int r)
{ return l <= x && x < r; }
inline bool isVal(int i, int j)
{ return ( inRange(0,i,n) && inRange(0,j,m) ); }

// [0,2b) pretas
// [2b,2b+w) brancas
// [2b+w] src
// [2b+w+1] snk
int head[MV], dist[MV], q[MV], curr[MV];
int to[ME], next[ME], f[ME], cap[ME], es;
node src, snk;

inline void add(node u, node v, num cuv)
{
    to[es] = v; f[es] = 0; cap[es] = cuv;
    next[es] = head[u]; head[u] = es++;

    to[es] = u; f[es] = 0; cap[es] = 0;
    next[es] = head[v]; head[v] = es++;
}
void bfs()
{
    int qf = 0,
        qb = 0;
    for(int i=0;i<snk+1;i++)
        dist[i] = -1;
    dist[src] = 0;
    q[qb++] = src;
    while( qf < qb )
    {
        node u = q[qf++];
        for(edge e=head[u];e>=0;e=next[e])
            if( dist[to[e]] == -1 && cap[e] > f[e] )
            {
                dist[to[e]] = dist[u] + 1;
                q[qb++] = to[e];
            }
    }
}

int dfs(node u, num af)
{
    if( u == snk  )
        return af;
    int aux;
    for(edge& e=curr[u];e>=0;e=next[e])
        if( cap[e] > f[e] && 
            dist[to[e]] == dist[u] + 1 &&
            (aux=dfs(to[e],min(af,cap[e]-f[e]))))
        {
            f[e] += aux;
            f[e^1] -= aux;
            return aux;
        }
    return 0;
}

int maxFlow()
{
    int ans = 0;
    for(bfs(); dist[snk] != -1; bfs())
    {
        for(node v=0;v<snk+1;v++)
            curr[v] = head[v];
        while(42)
        {
            int aux = dfs(src,INT_MAX);
            if(aux>0)
                ans += aux;
            else
                break;
        }
    }
    return ans;
}


int main()
{

    scanf("%d", &tc);

    while (tc--) {
        memset(id, -1, sizeof id);
        memset(head, -1, sizeof head);
        es = 0;
        scanf("%d %d", &n, &m);
        b = w = 0;

        for (int i = 0; i < n; i++){ 
            scanf(" %s", in[i]);
            for(int j=0;j<m;j++)
            {
                if( in[i][j] == '.' )
                    continue;
                if( in[i][j] == 'B' )
                    id[i][j] = b++;
                else
                    id[i][j] = w++;
            }
            
        }
        if (w != 2*b) {
            printf("NO\n");
            continue;
        }
        src = 2*b + w;
        snk = src + 1;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
            {
                if (in[i][j] == 'B') {
                    add(src, 2*id[i][j] ,1);
                    add(src, 2*id[i][j]+1,1);
                    for(int k=0;k<4;k++)
                    {
                        int tx = i+dx[k],
                            ty = j+dy[k];
                        if (!isVal(tx, ty))
                            continue;
                        if( in[tx][ty] == 'W' )
                        {
                            add(2*id[i][j]+(k<2), 2*b+id[tx][ty],1);
                        }
                    }
                } else if (in[i][j] == 'W')
                    add(2*b+id[i][j], snk, 1);
            }
        if( 2*b == maxFlow() )
            printf("YES\n");
        else
            printf("NO\n");
    }
}
