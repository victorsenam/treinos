#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 112345;
ll a[N];
int b[N], p[N];

int main () {
#ifdef ONLINE_JUDGE
	freopen("hell.in", "r", stdin);
	freopen("hell.out", "w", stdout);
#endif
	int n, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%lld", &a[i]), p[i] = i;
	ll tot = accumulate(a, a + n, 0ll);
	if(tot & 1) { puts("No"); return 0; }
	sort(p, p + n, [](int i, int j) { return a[i] < a[j]; });
	tot /= 2;
	for(i = n - 1; i >= 0; i--)
		if(tot >= a[p[i]]) {
			tot -= a[p[i]];
			b[p[i]] = 1;
		} else b[p[i]] = -1;
	puts("Yes");
	for(i = 0; i < n; i++) printf("%d ", b[i]);
	putchar('\n');
}
