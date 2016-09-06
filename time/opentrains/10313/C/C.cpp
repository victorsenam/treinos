#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 5e5;
const int M = 5e5;

int ok;
int n, m, vs, ps;
int ad[N], pre[N], st[N], ss, comp[N], v[N];
int to[M], nx[M], w[M], es=1;

int dfs(int i){
	int ans = (pre[i] = ++ps);
	st[ss++] = i;
	for(int e=ad[i];e;e=nx[e])
		if(!pre[to[e]])       ans = min(ans, dfs(to[e]));
		else if(!comp[to[e]]) ans = min(ans, pre[to[e]]);
	if(ans == pre[i]) {
		while(ss > 0 && st[ss-1] != i) comp[st[--ss]] = vs;
		comp[st[--ss]] = vs++;
	}
	return ans;
}

void build(int i){
	pre[i] = 1;
	int ni = comp[i];
	for(int e=ad[i];e;e=nx[e]) {
		if(!pre[to[e]]) build(to[e]);
		int nj = comp[to[e]];
		if(ni == nj) ok &= !w[e];
		else {
			w[es] = w[e];    to[es] = nj;
			nx[es] = ad[ni]; ad[ni] = es++;
		}
	}
}

void fval(int i){
	int _min = -2e9;
	pre[i] = 1;
	for(int e=ad[i];e;e=nx[e]){
		if(!pre[to[e]]) fval(to[e]);
		_min = max(_min, w[e] + v[to[e]]);
	}
	v[i] = _min;
}

void check(int i){
	pre[i] = 1;
	for(int e=ad[i];e;e=nx[e]){
		if(!pre[to[e]]) check(to[e]);
		ok &= (v[to[e]] + w[e] <= v[i]);
	}
}

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf(" %d%d", &m, &n);
	for(int k=0;k<m;k++) {
		int t0, t1, x0, x1, i, j;
		scanf(" %d%d%d%d%d", w+es, &t0, &x0, &t1, &x1);
		if(t0) v[i=vs++] = x0;
		else i = --x0;
		if(t1) v[j=vs++] = x1;
		else j = --x1;
		to[es] = i; nx[es] = ad[j]; ad[j] = es++;
	}
	m = vs;
	for(int i=0;i<m;i++) if(!pre[i]) dfs(i);
	ok = 1;
	for(int i=0;i<m;i++) pre[i] = 0;
	for(int i=0;i<m;i++) if(!pre[i]) build(i);

	if(!ok) { puts("NO"); return 0; }
	for(int i=m;i<vs;i++) v[i] = -1;
	for(int i=n;i<m;i++)
		if(v[comp[i]] == -1) v[comp[i]] = v[i];
		else if(v[comp[i]] != v[i]) { puts("NO"); return 0; }
	for(int i=m;i<vs;i++) if(!pre[i]) fval(i);
	for(int i=m;i<vs;i++) pre[i] = 0;
	for(int i=m;i<vs;i++) if(!pre[i]) check(i);
	if(ok){
		puts("YES");
		for(int i=0;i<n;i++) printf("%d\n", v[comp[i]]);
	} else puts("NO");
}
