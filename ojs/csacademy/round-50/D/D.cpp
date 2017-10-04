#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
int a[N], b[N], p[N];
int n, k;

int main () {
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a[i], &b[i]);
		p[i] = i;
	}

	sort(p, p+n, [] (int i, int j) { return b[i] < b[j]; });

	multiset<int> pq;

	for (int _i = 0; _i < n; _i++) {
		int i = p[_i];
		auto it = pq.lower_bound(a[i]);
		if (it != pq.begin())
			pq.erase(prev(it));
		pq.insert(a[i]);
	}

	printf("%d\n", pq.size());
}
