#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;
const int M = 2e5+7;

int n, m;
int hd[N], nx[M], to[M], es;
int hg[N], siz[N];
int visi[N], turn;
int c_pr[N];
vector<int> c_adj[N];

int dfs (int u) {

}

int build (int u) {
    int size = dfs(u);
    int nx = u;
    int ed = -1;

    while (ed) {
        for (ed = hd[u]; ed && (c_pr[to[ed]] == -1 || siz[to[ed]] + siz[to[ed]] <= size); ed = nx[ed]);
        if (ed) u = to[ed];
    }
    
    
}

int main () {
    memset(c_pr, -1, sizeof c_pr);
    scanf("%d %d", &n, &m);

    es = 2;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        to[es] = b; nx[es] = hd[a]; hd[a] = es++;
        to[es] = a; nx[es] = hd[b]; hd[b] = es++;
    }

    build(0);
}
