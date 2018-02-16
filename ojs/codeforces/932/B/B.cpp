#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int mg[N];
int q;
vector<int> wh[12];

int f (int n) {
	int res = 1;
	while (n) {
		if (n%10) res *= (n%10);
		n /= 10;
	}
	return res;
}

int g (int n) {
	if (mg[n] != -1) return mg[n];
	if (n < 10) return mg[n] = n;
	return mg[n] = g(f(n));
}

int main () {
	memset(mg, -1, sizeof mg);
	for (int i = 1; i < N; i++)
		wh[g(i)].pb(i);

	scanf("%d", &q);
	while (q--) {
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", upper_bound(wh[k].begin(), wh[k].end(), r) - lower_bound(wh[k].begin(), wh[k].end(), l));
	}
}
