#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct evt {
	int i, l, r;

	bool operator < (const evt & ot) const {
		return l < ot.l;
	}
};

const int N = 1e5+7;

int n;
vector<evt> v;
string str[N];

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> str[i];
		int ln = str[i].size();
		int k;
		cin >> k;

		for (int j = 0; j < k; j++) {
			evt cur;
			cur.i = i;
			cin >> cur.l;
			cur.l--;
			cur.r = cur.l + ln;
			v.pb(cur);
		}
	}

	sort(v.begin(), v.end());

	int i = 0;
	int ev = 0;
	evt att({0,0,0});

	while (att.r > i || ev < v.size()) {
		while (ev < v.size() && v[ev].l <= i) {
			if (v[ev].r >= att.r)
				att = v[ev];
			ev++;
		}

		if (att.r <= i)
			cout << "a";
		else
			cout << str[att.i][i-att.l];
		i++;
	}
	cout << endl;
}
