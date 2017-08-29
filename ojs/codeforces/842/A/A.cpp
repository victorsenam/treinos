#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll l, r, x, y, k;

int main () {
	cin >> l >> r >> x >> y >> k;

	for (ll i = l; i <= r; i++) {
		if (i%k == 0 && i/k >= x && i/k <= y) {
			cout << "YES" << endl;
			return 0;
		}
	}

	cout << "NO" << endl;
}
