#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

int n;
ll v[N];
priority_queue<ll> pq;

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lld", &v[i]);
		pq.push(-v[i]);
	}

	ll res = 0;
	while (pq.size() > 1) {
		ll s = 0;

		s -= pq.top();
		pq.pop();
		s -= pq.top();
		pq.pop();
		if (pq.size()%2) {
			s -= pq.top();
			pq.pop();
		}
		res += s;
		pq.push(-s);
	}

	printf("%lld\n", res);
}
