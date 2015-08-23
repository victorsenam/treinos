#include <bits/stdc++.h>
#define inf (int)1e9 
#define all(v) (v).begin(), (v).end()
#define close(a,i,c) (((a)<=(i)) && ((i)<=(c)))
#define open(a,i,c) (((a)<(i)) && ((i)<(c)))
#define up(i,n) for( i = 0; i < n ; i++)
#define down(i,n) for( i = n; i >= 0; i--)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
#define ii pair<int,int>
using namespace std;

#define MAX 100042

int dist[MAX];
vector< ii > graph[MAX];

void djs(int s, int d)
{
    int i;
    // But the source
    dist[s] = 0;
    set< ii > Q;

    Q.insert( ii(0,s) );
    while( !Q.empty() )
    {
        int v = Q.begin()->second;
        Q.erase(Q.begin());

        if( v == d )
            break;
        else
            up(i, graph[v].size())
            {
                int u = graph[v][i].second, wu = graph[v][i].first;
                if( dist[u] > dist[v] + wu )
                {
                    if( dist[u] != inf )
                        Q.erase(Q.find(ii(dist[u],u)));

                    dist[u] = dist[v] + wu;
                    Q.insert( ii(dist[u], u) );
                } 
            }

    }
}

int main()
{
    int i, j, tc, n, m, s, d, from, to, w;
    scanf("%d", &tc);
    up(i, tc)
    {
        scanf("%d %d %d %d", &n, &m, &s, &d);

        up(j, n)
            graph[j].clear();

        up(j, m)
        {
            scanf("%d %d %d", &from, &to, &w);
            graph[from-1].push_back( ii(w, to-1) );
            graph[to-1].push_back( ii(w, from-1) );
        }

        up(j,n)
            dist[j] = inf;

        djs(s-1, d-1);
        if(dist[d-1] == inf)
            printf("NONE\n");
        else
            printf("%d\n",dist[d-1]);
    }
}
