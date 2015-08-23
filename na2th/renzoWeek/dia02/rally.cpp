#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 101;

int id[MV], dist[MV][MV];

num n, m, s;
bool cyc, found;

int find(node u)
{ return (id[u] < 0) ? u : (id[u] = find(id[u])) ; }
bool merge(node u, node v)
{
    if( (u=find(u)) == (v=find(v)) )
        return false;
    if( id[v] < id[u] ) swap(u,v);
    id[u] += id[v]; id[v] = u;
    return true;
}

int main()
{
    memset(id, -1, sizeof id);
    cin >> n >> m >> s;
    cyc   = false;
    found = false;

    for(int i=0;i<n*n;i++)
        dist[i/n][i%n] = INT_MAX;
    for(node v=0;v<n;v++)
        dist[v][v] = 0;

    for(int i=0;i<m;i++)
    {
        node u,v; num c;
        cin >> u >> v >> c;
        u--;v--;
        dist[u][v] = dist[v][u] = c;
        cyc |= !merge(u,v);
    }
    found = cyc;
    for(node i=0;i<n;i++)
    for(node u=0;u<n;u++)
    for(node v=0;v<n;v++)
        dist[u][v] = min(1ll*dist[u][v], 1ll*dist[u][i]+1ll*dist[i][v]);

    for(int i=0;!found && i<n*n;i++)
        found |= ( dist[i/n][i%n] != INT_MAX && dist[i/n][i%n] >= s);

    if(found)
        cout << "YES\n";
    else
        cout << "NO\n";
}
