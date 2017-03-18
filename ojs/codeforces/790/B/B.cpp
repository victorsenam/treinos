#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5+7;
const int K = 8;

int n, k;
ll x[N][K][2];
vector<int> adj[N];

ll dfs (int u, int p) {
    ll res = 0;
    ll loc = 0;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == p) continue;
        res += dfs(v, u);
        
        for (int a = 1; a <= k; a++) {
            for (int b = 1; b <= k; b++) {
                loc += x[u][a][1]*x[v][b][0] + x[u][a][0]*x[v][b][1];
                if (a + b > k) {
                    loc -= x[u][a][0]*x[v][b][0];
                }
            }
        }

        for (int a = 1; a <= k; a++) {
            x[u][a][0] += x[v][a][0];
            x[u][a][1] += x[v][a][1];
            loc += x[v][a][1];
        }
    }

    res += loc;
    
    x[u][k][0]++;
    x[u][k][1]++;
    for (int b = 1; b <= k; b++) {
        x[u][b-1][0] = x[u][b][0];
        x[u][b-1][1] = x[u][b][1];
    }
    x[u][k][0] = x[u][k][1] = 0;
    x[u][k-1][0] += x[u][0][0];
    x[u][k-1][1] += x[u][0][0] + x[u][0][1];
    
    return res;
}

int main () {
    scanf("%d %d", &n, &k);
    k++;

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    printf("%lld\n", dfs(0, 0));
}
