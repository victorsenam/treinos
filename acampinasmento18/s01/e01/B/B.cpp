#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int M = 212345;
int en = 2;

int nx[M], he[M], fl[M], to[M], seen[M];

void add_edge(int a, int b) {
	nx[en] = he[b]; to[en] = a; fl[en] = 0; he[b] = en++;
	nx[en] = he[a]; to[en] = b; fl[en] = 0; he[a] = en++;
}

int tempo;
bool dfs(int s, int t) {
	if(s == t) return true;
	if(seen[s] == tempo) return false;
	seen[s] = tempo;
	for(int e = he[s]; e; e = nx[e])
		if(((e & 1) - fl[e]) && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

int main () {
	int i, n, m, x;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		while(scanf("%d", &x) != EOF && x)
			add_edge(i, x - 1 + n);
	int s = n + m;
	int t = n + m + 1;
	for(i = 0; i < n; i++) add_edge(s, i);
	for(i = 0; i < m; i++) add_edge(i + n, t);
	int ans = 0; tempo++;
	while(dfs(s, t))
		ans++, tempo++;
	printf("%d\n", ans);
	for(i = 0; i < n; i++)
		for(int e = he[i]; e; e = nx[e])
			if(fl[e] && to[e] >= n && to[e] < s)
				printf("%d %d\n", i + 1, to[e] - n + 1);
}
