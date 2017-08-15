#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 20;
const int T = (1<<N);

int n;
int rs[T];

void printa (int mask) {
	while (mask) {
		cout << (mask&1) << " ";
		mask /= 2;
	}
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int lst = 0;
	for (int mask = 0; mask < T; mask++) {
		//if (__builtin_popcount(mask) != kk) continue;
		int i = 0;
		for (i = 0; i <= N; i++) {
			bool ok = 1;

			for (int r = 0; ok && r < N; r++) {
				if (!(mask&(1<<r))) continue;
				
				ok = !(rs[mask - (1<<r)] == i);
				for (int a = 0; ok && a < r; a++)
					ok = !(rs[(mask - (1<<r))^(1<<a)] == i);
			}

			if (ok)
				break;
		}

		rs[mask] = i;
		if (mask >= 5000 && rs[mask] == 0) {
			cout << mask << " " << mask - lst << endl;
			lst = mask;
		}
	}

	return 0;
	int ls = 0;
	int qt = 0;
	for (int i = 0; i < T; i += 16) {
		int mn = 8;
		vector<int> v;
		for (int j = 0; j < 16; j++) {
			assert(rs[i+j] == rs[(i+j)^7]);
			if ((i+j)%8 < 4) continue;
			mn = min(mn, rs[i+j]);
			v.pb(rs[i+j]);
			//cout << rs[i+j] << " ";
		}
		sort(v.begin(), v.end());
		for (int j = 0; j < 8; j++)
			cout << v[j] << " ";
		cout << endl;
		continue;

		if (mn == ls) {
			qt++;
		} else {
			cout << ls << " -> " << qt << endl;
			qt = 0;
			ls = mn;
		}
	}
}
