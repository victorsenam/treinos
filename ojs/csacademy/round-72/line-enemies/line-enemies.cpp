#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

set<pii> a, b;

int main () {
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		int l, r;
		cin >> l >> r;
		if (t == 3) {
			int s, t;
			cin >> s >> t;
			if (l == s && r == t) cout << 0 << endl;
			else if (r < s || l > t) cout << 1 << endl;
			else if (a.size() && a.rbegin()->first > max(r,t)) cout << 2 << endl;
			else if (b.size() && b.begin()->first < min(l,s)) cout << 2 << endl;
			else if (a.size() && a.rbegin()->first > r && b.begin()->first < s) cout << 3 << endl;
			else if (a.size() && a.rbegin()->first > t && b.begin()->first < l) cout << 3 << endl;
			else cout << -1 << endl;
		} else {
			if (t == 1) { a.insert(pii(l,r)); b.insert(pii(r,l)); }
			else { a.erase(pii(l,r)); b.erase(pii(r,l)); }
		}
	}
}
