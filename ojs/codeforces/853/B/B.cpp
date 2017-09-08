#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
const int M = 1e6+7;

int n, m, k;
int d[N], f[N], t[N], c[N];
ll bst[N];
ll res, cost;
int cnt;

vector<int> go_back[N];
vector<int> go_to;

struct evt {
	int i;

	int val () const {
		return d[go_back[i].back()];
	}
	
	bool operator < (const evt & ot) const {
		if (val() != ot.val())
			return val() > ot.val();
		return i < ot.i;
	}
};

priority_queue<evt >pq;

void done () {
	if (res == LLONG_MAX)
		res = -1;
	printf("%lld\n", res);
	exit(0);
}

int main () {
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &d[i], &f[i], &t[i], &c[i]);
		
		if (t[i] == 0)
			go_to.pb(i);
		else
			go_back[t[i]].pb(i);
	}
	d[m] = -1;
	c[m] = 0;

	for (int i = 1; i <= n; i++) {
		go_back[i].pb(m);
		sort(go_back[i].begin(), go_back[i].end(), [] (int i, int j) {
			return c[i] > c[j];
		});

		bst[i] = -1;
		pq.push(evt({i}));
	}

	sort(go_to.begin(), go_to.end(), [] (int i, int j) {
		return d[i] < d[j];
	});

	int i = 0;
	cnt = 0;
	cost = 0;
	res = LLONG_MAX;
	for (int s = 0; s < M; s++) {
		while (!pq.empty() && pq.top().val() < s+k) {
			evt cur = pq.top();
			pq.pop();

			cost -= c[go_back[cur.i].back()];
			go_back[cur.i].pop_back();
			if (go_back[cur.i].size()) {
				cost += c[go_back[cur.i].back()];
				pq.push(cur);
			} else {
				done();
			}
		}

		while (i < go_to.size() && d[go_to[i]] < s) {
			int j = go_to[i];
			if (bst[f[j]] == -1) {
				cnt++;
				bst[f[j]] = c[j];
				cost += c[j];
			} else if (bst[f[j]] > c[j]) {
				cost -= bst[f[j]];
				bst[f[j]] = c[j];
				cost += bst[f[j]];
			}
			i++;
		}

		if (cnt == n) {
			//cout << s << " valid day" << endl;
			res = min(res, cost);
		}
	}

	done();
}
