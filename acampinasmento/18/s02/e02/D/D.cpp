#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 250007;

int n, m, k;
int v[N];

int main () {
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}
	sort(v, v+n);

	ll res = 0;
	for (int i = 0; i < m; i++) {
		int a;
		scanf("%d", &a);

		res += upper_bound(v, v+n, a+k) - lower_bound(v,v+n, a-k);
	}
	printf("%lld\n", res);
	
}
