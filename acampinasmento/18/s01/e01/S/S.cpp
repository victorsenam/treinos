#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5e3+7;

int n;
pii v[N];

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].first, &v[i].second);
		if (v[i].first > v[i].second) swap(v[i].first, v[i].second);
	}
	
	sort(v, v+n);
	ll l = -1e9, r = -1e9;
	ll res = 0;
	for (int i = 0; i < n; i++) {
		if (v[i].first > r) {
			res += r - l;
			l = v[i].first;
			r = v[i].second;
		} else {
			r = max(v[i].second, r);
		}
	}
	res += r - l;
	printf("%lld\n",res);
}
