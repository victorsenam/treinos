#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fst first
#define snd second
const ll modn = 1000000007;
ll mod(ll x) { return x % modn; }

char g[11][11];
int h, w, n;
char& gr(pii p) { return g[p.fst][p.snd]; }
pii p[4];

ll hsh() {
	ll hh = 0;
	for(int i = 0; i < n; i++)
		hh = mod(hh * 127ll + p[i].fst * 10 + p[i].snd);
	return hh;
}
pii fin;
int mx;
unordered_map<ll, int> seen;
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};
inline bool valid(int i, int j) { return i >= 0 && i < h && j >= 0 && j < w && g[i][j] == '.'; }
void solve(int mv) {
	if(mv >= mx) return;
	if(p[0] == fin) { mx = mv; return; }
	ll hh = hsh();
	if(seen.count(hh) && seen[hh] <= mv) { return; }
	seen[hh] = mv;
	for(int r = 0; r < n; r++)
		for(int d = 0; d < 4; d++) {
			pii bak = p[r];
			int i = p[r].fst + di[d], j = p[r].snd + dj[d];
			if(!valid(i, j)) continue;
			while(valid(i, j)) i += di[d], j += dj[d];
			i -= di[d]; j -= dj[d];
			p[r] = pii(i, j);
			swap(gr(p[r]), gr(bak));
			solve(mv + 1);
			swap(gr(p[r]), gr(bak));
			p[r] = bak;
		}
}

int main() {
	int i, j, l;
	while(scanf("%d %d %d %d", &n, &w, &h, &l) != EOF) {
		mx = l + 1;
		for(i = 0; i < h; i++)
			for(j = 0; j < w; j++) {	
				scanf(" %c", &g[i][j]);
				if(g[i][j] == 'X') { fin = pii(i, j); g[i][j] = '.'; }
				if(isdigit(g[i][j])) p[g[i][j] - '1'] = pii(i, j);
			}
		seen.clear();
		solve(0);
		if(mx == l + 1) puts("NO SOLUTION");
		else printf("%d\n", mx);
	}
}
