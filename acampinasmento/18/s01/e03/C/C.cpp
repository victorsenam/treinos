#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, m;
ll a[260 * 260];

ll memo[260][260];
ll solve(int a, int b) {
	if(a == n && b == m) return 0;
	ll &r = memo[a][b];
	if(r != -1) return r;
	r = 1e16;
	if(a < n) r = ::a[a * b] + solve(a + 1, b); 
	if(b < m) r = min(r, ::a[a * b] + solve(a, b + 1));
	return r;
}

int main() {
	memset(memo, -1, sizeof memo);
	int i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n * m; i++)
		scanf("%lld", &a[i]);
	sort(a, a + n * m, greater<int>());
	printf("%lld\n", (a[0] * 2 + solve(1, 1)) * 2);
}
