#include <bits/stdc++.h>

using namespace std;

vector<int> graph[10500];
int distA[10500] = {-1};
int distB[10500] = {-1};

void bfs(int v, int * dists)
{
    queue<int> Q;
    dists[v] = 0;
    Q.push(v);

    while( !Q.empty() )
    {
        int node = Q.front();
        Q.pop();

        for( int i = 0; i < graph[node].size() ; i++ )
        {
            int viz = graph[node][i];
            if( dists[viz] == -1 )
            {
                dists[viz] = dists[node] + 1;
                Q.push(viz);
            }
        }
    }
}

int main()
{
    int n, c;
    scanf("%d", &n);
    memset( distA, -1, n*sizeof(int));
    memset( distB, -1, n*sizeof(int));
    c = n-1;

    while( c-- > 0 )
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    bfs(0, distA);
    int u = (max_element(distA, distA+n) - distA);

    bfs(u, distB);
    int v = *max_element(distB, distB+n);
    printf("%d\n", v);
}
