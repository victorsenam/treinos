#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 500000;

struct point {
	int p;
	int l, c;

	bool operator < (const point & ot) const {
		if (l != ot.l)
			return l < ot.l;
		return c < ot.c;
	}
};

point res[2];
char rr;

int dist (point a, point b) {
	return abs(a.l - b.l) + abs(a.c - b.c);
}

void test (point a, point b, char r) {
	bool chg = 0;
	if (res[0].p == -1) {
		chg = 1;
	} else {
		int d = dist(a, b);
		int e = dist(res[0], res[1]);

		if (d < e) chg = 1;
		else if (d == e) {
			if (a.p < res[0].p) chg = 1;
			else if (a.p == res[0].p) {
				chg = (b.p > res[1].p);
			}
		}
	}

	if (chg) {
		res[0] = a;
		res[1] = b;
		rr = r;
	}
}

int ts;
map<int, set<point> > mp[2];
int n;
char str[N];

int main () {
	scanf("%d", &ts); 

	while (ts--) {
		mp[0].clear(); mp[1].clear();
		res[1].p = res[0].p = -1;

		scanf("%d %s", &n, str);

		point att({0,0,0});
		for (int i = 0; i < n; i++) {
			mp[0][att.l].insert(att);
			mp[1][att.c].insert(att);

			att.p++;

			if (str[i] == 'N')
				att.l--;
			else if (str[i] == 'E')
				att.c--;
			else if (str[i] == 'S')
				att.l++;
			else
				att.c++;

			if (str[i] != 'N') {
				set<point> & s = mp[1][att.c];
				auto it = s.lower_bound(att);
				if (it != s.end())
					test(*it, att,'N');
			}
			if (str[i] != 'E') {
				set<point> & s = mp[0][att.l];
				auto it = s.lower_bound(att);
				if (it != s.end())
					test(*it, att,'E');
			}
			if (str[i] != 'S') {
				set<point> & s = mp[1][att.c];
				auto it = s.lower_bound(att);
				if (it != s.begin()) {
					--it;
					test(*it, att,'S');
				}
			}
			if (str[i] != 'W') {
				set<point> & s = mp[0][att.l];
				auto it = s.lower_bound(att);
				if (it != s.begin()) {
					--it;
					test(*it, att,'W');
				}
			}

		}

		printf("%d %d %d %c\n", dist(res[0], res[1]), res[0].p, res[1].p, rr);
		if (ts)
			printf("\n");
	}
}
