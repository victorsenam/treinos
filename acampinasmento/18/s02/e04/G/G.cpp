#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct slot {
	bool empty;
	ll s, d;
	bool operator < (const slot & o) const { return s < o.s; }
};

struct spa {
	ll s, d;
	bool operator < (const spa & o) const { return (d!=o.d)?d<o.d:s<o.s; }
};

ll d; int q;
set<slot> s;
set<spa> r;
map<string,ll> pos;
char c, str[13];
ll l;

int main () {
	scanf("%lld %d", &d, &q);

	s.insert({1,0,d}); r.insert({0,d});
	for (int i = 0; i < q; i++) {
		scanf(" %c %s", &c, str);

		if (c == 'P') {
			scanf("%lld", &l);
			auto it = r.lower_bound({0,l});
			if (it == r.end()) printf("NIE\n");
			else {
				slot cur({0,it->s,l});
				slot emp({1,it->s+l,it->d-l});
				pos[str] = cur.s;
				s.erase({ 1, it->s, it->d }); r.erase(it); s.insert(cur);
				if (emp.d > 0) { s.insert(emp); r.insert({emp.s,emp.d}); }
				printf("%lld\n", cur.s);
			}
		} else {
			if (pos.find(str) == pos.end()) {
				printf("BRAK\n");
			} else {
				printf("OK\n");
				ll x = pos[str];
				pos.erase(str);

				auto it = s.lower_bound({0,x,0});
				slot cur = *it;
				cur.empty = 1;
				if (next(it) != s.end()) {
					if (next(it)->empty) {
						cur.d += next(it)->d;
						r.erase({next(it)->s,next(it)->d});
						s.erase(next(it));
					}
				}
				if (it != s.begin()) {
					if (prev(it)->empty) {
						cur.d += prev(it)->d;
						cur.s = prev(it)->s;
						r.erase({prev(it)->s,prev(it)->d});
						s.erase(prev(it));
					}
				}
				r.erase({ it->s, it->d }); s.erase(it);
				s.insert(cur); r.insert({cur.s,cur.d});
			}
		}
	}
}
