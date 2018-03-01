#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e6+7;

int l, r;
int n, q;
ll x[N];

int main () {
	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++)
		scanf("%lld", &x[i]);
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &l, &r);
		vector<int> v;
		l--; r--;
		for (int k = l; k <= r && k <= l + 100; k++)
			v.pb(k);
		sort(v.begin(), v.end(), [] (int i, int j) { return x[i] < x[j]; });

		bool ok = 0;
		for (int k = 2; !ok && k < v.size(); k++) {
			if (x[v[k-2]] + x[v[k-1]] > x[v[k]]) {
				ok = 1;
				printf("%d %d %d\n", v[k-2]+1, v[k-1]+1, v[k]+1);
			}
		}
		if (!ok) printf("-1\n");
	}
}
