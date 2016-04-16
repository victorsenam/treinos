#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e5+8;

int calc[N], dist[N];
vector<int> adj[N], d;
int n,m;

int dfs(int u, int p, int k) {
    calc[u] = 1;
    dist[u] = k;
    int r = u;
    for(int v : adj[u]) {
        if(v == p) continue;
        int l = dfs(v,u,k+1);
        if (dist[l] > dist[r])
            r = l;
    }
    return r;
}

int diam (int u) {
    u = dfs(u,u,0);
    u = dfs(u,u,0);
    return dist[u];
}

int main(){
    scanf("%d %d",&n,&m);    
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d",&u,&v);
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i = 0; i < n; i++) if(!calc[i]) d.pb(diam(i));

    sort(d.begin(), d.end());
    int k = d.size();
    int big = d[k-1];
    int i = 0, j = k-2;
    while(j>=0) {
        big = max(big,max(d[j], (d[j]+1)/2 + (big+1)/2 + 1)), j--;
    }
    printf("%d\n",big);
}
