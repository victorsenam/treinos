#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e4+7;

ll dp[2][N];
int n, m;
ll x[N], p[N], r[N], c[N];

int main () {
	int ts = 0;
	while (scanf("%d %d", &n, &m) != EOF) {
		if (!n) break;
		x[0] = -1e9-7;
		x[1] = 0;
		for (int i = 2; i <= n; i++) {
			scanf("%lld", &x[i]);
		}
		for (int i = 1; i <= n; i++)
			scanf("%lld", &c[i]);
		for (int i = 1; i <= n; i++)
			scanf("%lld", &r[i]);
		for (int i = 1; i <= n; i++)
			scanf("%lld", &p[i]);

		ll res = 0;
		for (int k = 0; k <= m; k++) {
			set<pii> s;
			deque<pii> st;
			bool b = (k&1);
			dp[b][0] = 0;
			for (int i = 1; i <= n; i++) {
				//cout << "(" << k << "," << i << ") -> " << x[i] << endl;
				dp[b][i] = dp[b][i-1] + p[i];
				//cout << "vazio = " << dp[b][i-1] + p[i] << endl;

				if (k > 0) {
					int lo = 0, hi = i-1;
					while (lo < hi) {
						int md = (lo+hi+1)/2;
						if (x[md] >= x[i] - r[i]) hi = md - 1;
						else lo = md;
					}
					ll loc = dp[!b][lo] + c[i];
					//cout << "cobre = " << loc << " para em " << lo << " custando " << c[i] << endl;
					
					lo = 0, hi = st.size();
					while (lo < hi) {
						int md = (lo+hi)/2;
						int j = st[md].second;
						if (x[j] >= x[i] - r[i]) hi = md;
						else lo = md+1;
					}
					if (lo < st.size()) loc = min(loc, st[lo].first + c[i]);

					dp[b][i] = min(dp[b][i], loc);
					
					while (s.size() && s.begin()->second < x[i]) s.erase(s.begin());
					if (s.size()) dp[b][i] = min(dp[b][i], s.begin()->first);
					//if (s.size()) cout << "aproveita = " << s.begin()->first << " limite " << s.begin()->second << endl;
					s.insert(pii(loc,x[i]+r[i]));

					while (st.size() && dp[!b][i] <= st.back().first) st.pop_back();
					st.pb(pii(dp[!b][i],i));
				}

				//cout << "deu " << dp[b][i] << endl;
			}

			if (k) res = min(res, dp[b][n]);
			else res = dp[b][n];
		}

		printf("Case %d: %lld\n", ++ts, res);
	}
}
