#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3;

ll a[N][N];
int t;
int n;
ll m[N][N];

int main () {
	scanf("%d", &t);

	while (t--) {
		ll res = -1;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				scanf("%lld", &a[i][j]);
			sort(a[i], a[i]+n);
			for (int j = 0; j < n; j++) {
				if (i) {
					m[i][j] = -1;
					int k = lower_bound(a[i-1],a[i-1]+n,a[i][j]) - a[i-1] - 1;
					if (k >= 0 && m[i-1][k] != -1)
						m[i][j] = max(m[i][j], m[i-1][k] + a[i][j]);
				} else {
					m[i][j] = a[i][j];
				}

				if (i == n-1)
					res = max(res, m[i][j]);
			}
		}
		printf("%lld\n", res);
	}
}
