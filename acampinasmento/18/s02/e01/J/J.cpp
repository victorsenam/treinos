#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

int n, d;
ll p;
ll w[N];
ll acc[N];
ll sum[N];
deque<ll> qu;

inline void add (deque<ll> & qu, ll x) {
	while (qu.size() && qu.back() < x) qu.pop_back();
	qu.push_back(x);
}

inline void rem (deque<ll> & qu, ll x) {
	if (qu.front() == x) qu.pop_front();
}

bool solve (int t) {
	cout << "== " << t << endl;
	qu.clear();
	for (int i = 0; i + d <= t; i++)
		add(qu, sum[i]);
	
	for (int i = 1; i + t <= n + 1; i++) {
		add(qu, sum[i+t-d]);
		rem(qu, sum[i-1]);

		cout << acc[i+t-1] - acc[i-1] << " - " << qu.front() << endl;
		if (p >= acc[i+t-1] - acc[i-1] - qu.front()) {
			return 1;
		}
	}
	return 0;
}

int main () {
	scanf("%d %lld %d", &n, &p, &d);

	acc[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &w[i]);
		acc[i] = acc[i-1] + w[i];
		if (i <= d) sum[1] += w[i];
	}

	cout << sum[1];
	for (int i = 2; i + d <= n + 1; i++) {
		sum[i] = sum[i-1] - w[i-1] + w[i+d-1];
		cout << " " << sum[i];
	}
	cout << endl;

	int lo = d, hi = n;
	while (lo < hi) {
		int md = (lo+hi+1)/2;
		if (solve(md)) lo = md;
		else hi = md-1;
	}

	printf("%d\n", lo);
}
