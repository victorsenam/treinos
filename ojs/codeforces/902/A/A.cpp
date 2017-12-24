#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, t;

int main () {
	cin >> n >> t;

	int m = 0;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;

		if (x <= m)
			m = max(m,y);
	}

	if (t <= m)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}
