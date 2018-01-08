#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct str {
	string s;
	int k, p;

	str () {}
	str (string t, int x, int y) : s(t), k(x), p(y) {}

	bool operator < (str o) const {
		if (o.s.size()*s.size() == 0) return (o.s.size() == 0);
		if (o.s.size() != s.size()) return s.size() < o.s.size();
		return s < o.s;
	}
};

const int N = (1<<8);

str bs[3][N];
set<str> pq;
string NO("!"), OP("("), CP(")"), AND("&"), OR("|");

void go (str e) {
	if (e < bs[e.k][e.p]) {
		if (bs[e.k][e.p].s.size())
			pq.erase(bs[e.k][e.p]);
		bs[e.k][e.p] = e;
		pq.insert(bs[e.k][e.p]);
	}
}

int n;

int main () {
	go(str(string("x"), 0, (1<<4)-1));
	go(str(string("y"), 0, ((1<<2)-1 + (((1<<2)-1)<<4))));
	go(str(string("z"), 0, 1+4+16+64));

	while (!pq.empty()) {
		str s = *pq.begin();
		pq.erase(pq.begin());

		if (s.k == 0) {
			go(str({ NO + s.s, 0, (1<<8) - 1 - s.p}));
			go(str({ s.s, 1, s.p}));

			for (int i = 0; i < N; i++)
				if (bs[1][i].s.size())
					go(str({ bs[1][i].s + AND + s.s, 1, bs[1][i].p & s.p }));
		} else if (s.k == 1) {
			go(str({ s.s, 2, s.p }));

			for (int i = 0; i < N; i++) {
				if (bs[0][i].s.size())
					go(str({ s.s + AND + bs[0][i].s, 1, bs[0][i].p & s.p }));
				if (bs[2][i].s.size())
					go(str({ bs[2][i].s + OR + s.s, 2, bs[2][i].p | s.p }));
			}
		} else {
			go(str({ OP + s.s + CP, 0, s.p }));

			for (int i = 0; i < N; i++) {
				if (bs[1][i].s.size())
					go(str({ s.s + OR + bs[1][i].s, 2, bs[1][i].p | s.p }));
			}
		}
	}

	int t;
	scanf("%d", &t);
	char str[10];
	for (int i = 0; i < t; i++) {
		scanf(" %s", str);
		int s = 0;
		for (int j = 0; j < 8; j++)
			s = s + s + (str[j] == '1');
		printf("%s\n", bs[2][s].s.c_str());
	}
}
