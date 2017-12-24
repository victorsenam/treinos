#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int t;
int n;
ll d;

int main () {
	cin >> t;
	while (t--) {
		cin >> n >> d;
		deque<pii> q;

		int res = n+1;
		int qt = 0;
		ll sum = 0;

		for (int i = 0; i < n; i++) {
			pii a;
			cin >> a.first;

			if (d <= 0) {
				if (a.first >= d)
					 res = 1;
				continue;
			}

			a.second = 1;
			sum += a.first;
			qt++;

			if (sum <= 0) {
				q.clear();
				sum = 0;
				qt = 0;
			} else {
				while (q.size() && a.first <= 0) {
					a.first += q.back().first;
					a.second += q.back().second;
					q.pop_back();
				}
				q.push_back(a);
				while (q.size() && sum - q.front().first >= d) {
					sum -= q.front().first;
					qt -= q.front().second;
					q.pop_front();
				}
				if (sum >= d)
					res = min(res, qt);
			}
		}

		if (res == n+1)
			res = -1;
		cout << res << endl;
	}
}
