#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;
map<ll, set<int> > mp;

void factor (ll x) {
	for (ll i = 2; i * i <= x; i++) {
		int cnt = 0;
		while (x%i == 0) {
			x /= i;
			cnt++;
		}
		if (cnt)
			mp[i].insert(cnt);
	}
	if (x != 1)
		mp[x].insert(1);
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		ll a;
		scanf("%lld", &a);
		factor(a);
	}
	
	int r = 0;
	for (pair<ll, set<int> > vl : mp) {
		r ^= 
	}
}
