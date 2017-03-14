#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100005

int n, m, a, b;
vector<int> adj[N];
ll maxi;
ll v[N];
bool seen[N];
int t;

ll dfs (int i) {
    if (seen[i]) return 0;

    seen[i] = 1;
    ll res = v[i];

    for (int j = 0; j < adj[i].size(); j++)
        res += dfs(adj[i][j]);
    
    return res;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            seen[i] = 0;
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        for (int i = 0; i < n; i++)
            scanf("%d", v+i);

        maxi = 0;
        for (int i = 0; i < n; i++)
            maxi = max(maxi, dfs(i));
        
        printf("%lld\n", maxi);
    }
}
