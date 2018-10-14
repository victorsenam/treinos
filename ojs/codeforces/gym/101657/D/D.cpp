#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

struct vec {
	ll x, y;
	bool operator < (const vec & o) const { return pii(x,y) < pii(o.x,o.y); }
};

struct seg {
	vec a, b;
	seg (vec _a, vec _b) : a(_a), b(_b) {}
	bool operator < (const seg & o) const {
		return pair<vec,vec>(min(a,b),max(a,b)) < pair<vec,vec>(min(o.a,o.b),max(o.a,o.b));
	}
};

vector<int> adj[N];
int cnt[N];
vec v[3];

int main () {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t, n;
	cin >> t;
	while (t--) {
		cin >> n;
		map<seg,int> mp;
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			cnt[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3; j++)
				cin >> v[j].x >> v[j].y;
			for (int j = 0; j < 3; j++) {
				seg s(v[j],v[(j+1)%3]);
				auto it = mp.find(s);
				if (it == mp.end()) mp[s] = i;
				else if (s.a.x < s.b.x) {
					adj[it->second].pb(i);
					cnt[i]++;
				} else if (s.a.x > s.b.x) {
					adj[i].pb(it->second);
					cnt[it->second]++;
				}
			}
		}

		queue<int> qu;
		for (int i = 0; i < n; i++) {
			if (cnt[i] == 0) qu.push(i);
		}

		while (!qu.empty()) {
			int u = qu.front();
			cout << u + 1 << " ";
			qu.pop();

			for (int v : adj[u]) {
				cnt[v]--;
				if (cnt[v] == 0) {
					qu.push(v);
				}
			}
		}
		cout << endl;
	}
}
