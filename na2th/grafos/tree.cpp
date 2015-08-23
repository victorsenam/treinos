#include <bits/stdc++.h>
#define MAX 10000

using namespace std;

vector<int> graph[MAX];
int visited[MAX];

void dfs(int v)
{
    visited[v] = 1;
    for(int i = 0; i < graph[v].size() ; i++)
        if( visited[graph[v][i]] == 0 )
            dfs(graph[v][i]);
}

int main()
{
    int n, m, foi, a, b;
    scanf("%d %d", &n, &m);

    for( int c = 0 ; c < m ; c++)
    {
        scanf("%d %d", &a, &b);
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    memset(visited, 0, n*sizeof(int));

    if( n != m+1 )
        printf("NO\n");
    else
    {
        dfs(0);
        foi = 1;
        for(int i = 0; i < n ; i++)
            foi &= ( visited[i] );

        if(foi)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
