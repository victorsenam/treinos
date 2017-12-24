#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int t, n;
string s;

int main () {
	cin >> t;
	while (t--) {
		cin >> n;
		int mx = 0;
		int mn = INT_MAX;
		map<string, int> mp;
		for (int i = 0; i < n; i++) {
			cin >> s;

			mp[s]++;
			if (mp[s] > mx)
				mx = mp[s];
			else
				mn = mp[s];
		}

		if (n == 0 || mx == mn) {
			cout << "Draw" << endl;
		} else if (mp.begin()->second == mx) {
			cout << mp.begin()->first << endl;
		} else {
			cout << mp.rbegin()->first << endl;
		}
	}
}
