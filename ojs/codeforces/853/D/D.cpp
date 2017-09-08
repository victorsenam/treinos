#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back


const int N = 3e5+7;
int n;
ll a[N];

int main () {
	scanf("%d", &n);

	ll lft = 0;
	ll bns = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
		lft += a[i];
	}
	
	ll res = 0;
	for (int i = 0; i < n; i++) {
		ll py = 0;
		if (lft - a[i] < bns + a[i]/10) {
			py = max(0ll, a[i]-bns);
			bns -= a[i]-py;
		} else {
			py = a[i];
		}

		res += py;
		bns += py/10;
		lft -= a[i];
	}
	
	printf("%lld\n", res);
}
