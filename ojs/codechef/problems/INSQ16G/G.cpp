#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e2+7;

int n;
int x[N], y[N], p[N];
set<pii> s;

bool inters (pii a, pii b) {
	return !(a.second <= b.first || b.second <= a.first);
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
		p[i] = i;
	}

	sort(p, p+n, [] (int i, int j) {
		if (x[i] != x[j])
			return x[i] < x[j];
		return y[i] < y[j];
	});

	ll pr = 0;
	ll ar = 0;
	ll ls = 0;
	ll sm = 0;
	bool fail = 0;

	for (int _i = 0; !fail && _i < n;) {
		int cur = p[_i];
		int fs = -1;
		cout << x[cur] << endl;

		ar += (x[cur]-ls)*sm;
		pr += (x[cur]-ls)*ll(s.size())*2ll;

		while (!fail && _i < n && x[p[_i]] == x[cur]) {
			int i = p[_i];
			if (fs == -1) {
				fs = y[i];
			} else {
				pii aux(fs, y[i]);
				pr += aux.second - aux.first;

				auto it = s.upper_bound(aux);
				bool ins = 0;
				if (it != s.end())
					fail |= inters(*it, aux);
				if (it != s.begin()) {
					--it;

					if (it->first <= aux.first && aux.second <= it->second) {
						ins = 1;
						sm -= aux.second - aux.first;

						if (it->first < aux.first) {
							cout << "+ " << it->first << " " << aux.first << endl;
							s.insert(pii(it->first, aux.first));
						}
						if (aux.second < it->second) {
							cout << "+ " << aux.second << " " << it->second << endl;
							s.insert(pii(aux.second, it->second));
						}
						cout << "- " << it->first << " " << it->second << endl;
						s.erase(it);
					} else {
						fail |= inters(*it, aux);
					}
				}

				if (!ins) {
					s.insert(aux);
					sm += aux.second - aux.first;
					cout << "+ " << aux.first << " " << aux.second << endl;
				}

				fs = -1;
			}
			_i++;
		}

		fail |= (fs != -1);

		for (auto it = s.begin(); it != s.end(); ++it) {
			if (it == s.begin()) continue;

			if (it->first == prev(it)->second) {
				pii aux(prev(it)->first, it->second);
				s.erase(prev(it));
				s.erase(it);
				it = s.insert(aux).first;
			}
		}

		ls = x[cur];
	}

	fail |= !s.empty();

	if (fail)
		printf("Impossible\n");
	else
		printf("%lld %lld\n", ar, pr);
}
