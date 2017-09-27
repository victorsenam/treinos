#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
ll memo[N][4];
int visi[N][4];

int n;
ll a[N], v[4];

ll pd (int i, int q) {
	if (q == 3)
		return 0;
	if (i == n)
		return LLONG_MIN;

	ll & me = memo[i][q];
	if (visi[i][q])
		return me;
	visi[i][q] = 1;

	me = pd(i+1, q);

	ll b = pd(i, q+1);
	if (b != LLONG_MIN)
		b += v[q]*a[i];
	me = max(b, me);
	return me;
}

int main () {
	scanf("%d %lld %lld %lld", &n, &v[0], &v[1], &v[2]);

	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	
	printf("%lld\n", pd(0,0));
}
