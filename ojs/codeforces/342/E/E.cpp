#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;
const int M = 2e5+7;
const int K = 30;

int n, m;
int hd[N], nx[M], to[M], es;
int de[N], siz[N];
int visi[N], turn;
int c_pr[N], pr[N];
int dist[K][N];
int root;
int res[N];

int dfs (int u, int depth, int d, int fr) {
	if (visi[u] == turn || c_pr[u] != -1) return 0;
	visi[u] = turn;

	pr[u] = fr;
	siz[u] = 1;
	dist[depth][u] = d;

	for (int ed = hd[u]; ed; ed = nx[ed])
		siz[u] += dfs(to[ed], depth, d+1, u);
	
	return siz[u];
}

int build (int u, int curr_de, int fr) {
	turn++;
    int size = dfs(u, curr_de-1, 1, fr);

    int ed = -1;
    while (ed) {
        for (ed = hd[u]; ed && (pr[u] == to[ed] || c_pr[to[ed]] != -1 || siz[to[ed]] + siz[to[ed]] <= size); ed = nx[ed]);
        if (ed) u = to[ed];
    }

	c_pr[u] = fr;
	de[u] = curr_de;
	dist[curr_de][u] = 0;

 	for (ed = hd[u]; ed; ed = nx[ed]) {
		if (c_pr[to[ed]] != -1) continue;

		build(to[ed], curr_de+1, u);
	}

	return u;
}

void update (int u) {
	int v = u;
	res[u] = 0;
	while (u != c_pr[u]) {
		u = c_pr[u];
		res[u] = min(res[u], dist[de[u]][v]);
	}
}

int get (int u) {
	int v = u;
	int ans = res[u];
	while (u != c_pr[u]) {
		u = c_pr[u];
		ans = min(ans, res[u] + dist[de[u]][v]);
	}
	return ans;
}

int main () {
    memset(c_pr, -1, sizeof c_pr);
    scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		res[i] = n+1;

    es = 2;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        to[es] = b; nx[es] = hd[a]; hd[a] = es++;
        to[es] = a; nx[es] = hd[b]; hd[b] = es++;
    }

    root = build(0, 1, 0);
	c_pr[root] = root;

	update(0);

	for (int i = 0; i < m; i++) {
		int ty, u;
		scanf("%d %d", &ty, &u);

		u--;

		if (ty == 1) {
			update(u);
		} else {
			printf("%d\n", get(u));
		}
	}
}
