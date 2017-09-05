#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int ts, n;

int main () {
	scanf("%d", &ts);

	while (ts--) {
		vector<int> r;
		set<int> s;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++) {
			int a;
			scanf("%d", &a);
			s.insert(a);

			while (*(s.rbegin()) > a) {
				r.pb(*(s.rbegin()));
				s.erase(prev(s.end()));
			}
		}
		printf("%d\n", (int) r.size());
		sort(r.begin(), r.end());
		for (int x : r)
			printf("%d\n", x);
	}
}
