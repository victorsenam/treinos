#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct pnt {
	int l, c;
	ll d;

	inline bool operator < (const pnt & o) const {
		return d > o.d;
	}
};

struct tng {
	pnt a, b;
	int t;
};

const int N = 2e3+7;
int n;
pnt s, t;
vector<int> cpr[2];
int m;
tng ret[N];
bitset<N> visi[N];

ll w[N][N][2];
ll dist[N][N];

void printa (pnt cur) {
	cout <<  cpr[0][cur.l] << "," << cpr[1][cur.c] << " | " << cur.d << endl;

}

int main () {
#ifdef ONLINE_JUDGE
	freopen("drive.in", "r", stdin);
	freopen("drive.out", "w", stdout);
#endif

	scanf("%d %d", &s.c, &s.l);
	scanf("%d %d", &t.c, &t.l);
	cpr[0].reserve(2+n + 4);
	cpr[1].reserve(2+n + 4);
	cpr[0].pb(s.l); cpr[0].pb(t.l);
	cpr[1].pb(s.c); cpr[1].pb(t.c);

	scanf("%d", &n);
	for (int i = 0; i < n; i++) { 
		scanf("%d %d", &ret[i].a.c, &ret[i].a.l);
		scanf("%d %d", &ret[i].b.c, &ret[i].b.l);
		scanf("%d", &ret[i].t);

		for (pnt a : {ret[i].a, ret[i].b}) {
			cpr[0].pb(a.l);
			cpr[1].pb(a.c);
		}
	}

	for (int k = 0; k < 2; k++) {
		sort(cpr[k].begin(), cpr[k].end());
		cpr[k].resize(unique(cpr[k].begin(), cpr[k].end()) - cpr[k].begin());
	}

	for (int l = 0; l < cpr[0].size(); l++) {
		for (int c = 0; c < cpr[1].size(); c++) {
			if (l+1 != cpr[0].size())
				w[l][c][0] = 10ll*(ll(cpr[0][l+1] - cpr[0][l]));
			if (c+1 != cpr[1].size())
				w[l][c][1] = 10ll*(ll(cpr[1][c+1] - cpr[1][c]));
			dist[l][c] = LLONG_MAX;
		}
	}

	for (int i = 0; i < n; i++) {
		int l0 = lower_bound(cpr[0].begin(), cpr[0].end(), ret[i].a.l) - cpr[0].begin();
		int c0 = lower_bound(cpr[1].begin(), cpr[1].end(), ret[i].a.c) - cpr[1].begin();

		for (int l = l0; cpr[0][l] < ret[i].b.l; l++)
			for (int c = c0+1; cpr[1][c] < ret[i].b.c; c++)
				w[l][c][0] = ll(cpr[0][l+1] - cpr[0][l])*(ll(ret[i].t));

		for (int l = l0+1; cpr[0][l] < ret[i].b.l; l++)
			for (int c = c0; cpr[1][c] < ret[i].b.c; c++)
				w[l][c][1] = ll(cpr[1][c+1] - cpr[1][c])*(ll(ret[i].t));
	}

	ll res = LLONG_MAX;
	pnt ini;
	ini.l = lower_bound(cpr[0].begin(), cpr[0].end(), s.l) - cpr[0].begin();
	ini.c = lower_bound(cpr[1].begin(), cpr[1].end(), s.c) - cpr[1].begin();
	ini.d = 0;

	priority_queue<pnt> pq;
	pq.push(ini);
	dist[ini.l][ini.c] = 0;

	while (!pq.empty()) {
		pnt cur = pq.top();
		pq.pop();

		if (visi[cur.l][cur.c]) continue;
		visi[cur.l][cur.c] = 1;

		//printa(cur);

		if (cpr[0][cur.l] == t.l && cpr[1][cur.c] == t.c) {
			t.d = dist[cur.l][cur.c];
			break;
		}

		pnt nx;
		if (cur.l + 1 != cpr[0].size()) {
			nx = cur;
			nx.l++;
			nx.d += w[cur.l][cur.c][0];
			if (dist[nx.l][nx.c] > nx.d) {
				dist[nx.l][nx.c] = nx.d;
				pq.push(nx);
			}
		}
		if (cur.c + 1 != cpr[1].size()) {
			nx = cur;
			nx.c++;
			nx.d += w[cur.l][cur.c][1];
			if (dist[nx.l][nx.c] > nx.d) {
				dist[nx.l][nx.c] = nx.d;
				pq.push(nx);
			}
		}
		if (cur.l != 0) {
			nx = cur;
			nx.l--;
			nx.d += w[nx.l][cur.c][0];
			if (dist[nx.l][nx.c] > nx.d) {
				dist[nx.l][nx.c] = nx.d;
				pq.push(nx);
			}
		}
		if (cur.c != 0) {
			nx = cur;
			nx.c--;
			nx.d += w[cur.l][nx.c][1];
			if (dist[nx.l][nx.c] > nx.d) {
				dist[nx.l][nx.c] = nx.d;
				pq.push(nx);
			}
		}

			//printf("GETS ");
			//printa(nx);

	}
	
	printf("%lld\n", t.d);
}
