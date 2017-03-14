#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 200007;
const int L = 60;
const num MAX = 1000000000000000000ll;

int n, m;
int lca[N][L];
num mul[N][L];
int hei[N];
num y;

int hd[N], nx[2*N], to[2*N], es;
num x[2*N];

int qrs;
int q[N][2];

inline num multiply (num a, num b) {
    if (a >= MAX || b >= MAX || a*b >= MAX || a*b < 0)
        return MAX;
    return a*b;
}

void dfs (int u, int fr) {
    if (fr != -1) {
        lca[u][0] = to[fr^1];
        mul[u][0] = x[fr];
        hei[u] = hei[to[fr^1]] + 1;
    }

    while (lca[u][lv-1] != -1) {
        int att = lca[u][lv-1];
        lca[u][lv] = lca[att][lv-1];
        mul[u][lv] = mul[att][lv-1]*mul[u][lv-1];
    }

    for (int ed = hd[u]; ed != -1; ed = nx[u]) {
        if ((ed|1) == (fr|1))
            continue;

        dfs(to[ed], ed);
    }
}

int main () {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i < n; i++) {
        int a, b;
        num w;
        scanf("%d %d %lld", &a, &b, &w);

        a--; b--;
        x[es] = w; nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        x[es] = w; nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }

    qrs = 0;
    lca[0][0] = -1;
    mul[0][0] = 1;
    hei[0] = 0;
    
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        if (qrs*qrs > n) {
            qrs = 0;
            dfs(0, -1);
        }
    }
}
