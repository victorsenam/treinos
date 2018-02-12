#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int main () {
#ifdef ONLINE_JUDGE
	freopen("giant.in", "r", stdin);
	freopen("giant.out", "w", stdout);
#endif
	ll Sw, Sh, Rw, Rh;
	cin >> Sw >> Sh >> Rw >> Rh;
	int n;
	cin >> n;
	ll best = LLONG_MAX;
	while(n--) {
		ll sw, sh, rw, rh, p;
		cin >> sw >> sh >> rw >> rh >> p;
		//if((Sw % sw) == 0 && (Sh % sh) == 0 && (Rw % w) == 0 && (Rh % h) == 0 && ll(Sw / sw) == ll(Rw / rw) && ll(Sh / sh) == ll(Rh / rh))
		best = min(best, p * max((Sw + sw - 1) / sw, (Rw + rw - 1) / rw) * max((Sh + sh - 1) / sh, (Rh + rh - 1) / rh));
		swap(sw, sh);
		swap(rw, rh);
		best = min(best, p * max((Sw + sw - 1) / sw, (Rw + rw - 1) / rw) * max((Sh + sh - 1) / sh, (Rh + rh - 1) / rh));
	}
	cout << best << "\n";
}
