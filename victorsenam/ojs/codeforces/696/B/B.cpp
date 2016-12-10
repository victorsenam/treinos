#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e6+7;

double siz[N];
double har[N];
double res[N];
int n;

vector<int> adj[N];

void dfs (int u) {
    siz[u] = 1;

    for (int v : adj[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
}

void calc (int u) {
    double bas = .5;
    for (int v : adj[u]) {
        res[v] = bas*double(siz[u]-1-siz[v]) + res[u] + 1.;
        calc(v);
    }
}

int main () {
    scanf("%d", &n);

    har[0] = 0.;
    for (int i = 1; i <= n; i++)  {
        har[i] = har[i-1] + 1./double(i);
    }

    for (int i = 1; i < n; i++) {
        int a;
        scanf("%d", &a);
        adj[a-1].push_back(i);
    }

    res[0] = 1.;
    dfs(0);
    calc(0);

    for (int i = 0; i < n; i++)
        printf("%.20f ", res[i]);
    printf("\n");
}
