#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5+7;

int dg[N];
int n;
int cr[N];
int cur;
vector<int> adj[N];

int dfs (int u, int x, int y, int p) {
    cur = max(cur, x); 
    cr[u] = x;

    int c = 1;

    for (int v : adj[u]) {
        if (v == p) continue;
        while (c == x || c == y) c++;
        dfs(v, c, x, u);
        c++;
    }
}

int main () {
    scanf("%d", &n);

    for (int i = 1; i < n; i++) { 
        int a, b;
        scanf("%d %d", &a, &b);
        dg[a]++; dg[b]++;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int res = 0;
    for (int i = 1; i <= n; i++)
        res = max(dg[i]+1, res);

    dfs(1, 1, 0, 0);
    //assert(cur == res);

    printf("%d\n", cur);
    for (int i = 1; i <= n; i++)
        printf("%d ", cr[i]);

}
