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

#define N 1000

int n, m;
int a, b;
vector<int> adj[N];
int v[N];
int mini;

int dfs(int i, int r) {
    if (v[i] == r) return 0;

    v[i] = r;
    int res = 1;

    for (int j = 0; j < adj[i].size(); j++)
        res += dfs(adj[i][j], r);

    return res;
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        v[i] = -1;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        adj[a-1].push_back(b-1);
    }

    mini = n;
    for (int i = 0; i < n; i++)
        mini = min(dfs(i, i), mini);

    printf("%d\n", mini);
}
