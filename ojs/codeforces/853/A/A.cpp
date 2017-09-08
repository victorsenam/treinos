#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 6e5+7;

set<int> s;
int p[N];
ll c[N];
int n, k;
int r[N];

int main () {
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		scanf("%lld", &c[i]);
		p[i] = i;
		s.insert(k+i);
	}

	sort(p, p+n, [] (int i, int j) {
		return c[i] > c[j];
	});

	ll cost = 0;
	for (int _i = 0; _i < n; _i++) {
		int i = p[_i];
		auto it = s.lower_bound(i);
		int j = *it;
		s.erase(it);

		r[i] = j+1;
		cost += ll(j-i)*c[i];
	}

	printf("%lld\n", cost);
	for (int i = 0; i < n; i++)
		printf("%d ", r[i]);
	printf("\n");
}
