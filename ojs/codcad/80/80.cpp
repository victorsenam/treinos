#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct card {
	int v; char n;
	bool operator == (card o) const { return v == o.v && n == o.n; }
	bool operator < (card o) const { return (v!=o.v)?v<o.v:n<o.n; }
};

const int N = 303;
const int P = 12;

int p, m, n;
card b[N];
vector<card> hand[P];
int t;

int main () {
	while (scanf("%d %d %d", &p, &m, &n) != EOF && p) {
		for (int i = 0; i < n; i++)
			scanf("%d %c", &b[i].v, &b[i].n);

		t = 0;
		for (int i = 0; i < p; i++) {
			hand[i].clear();
			for (int j = 0; j < m; j++)
				hand[i].pb(b[t++]);
		}

		int who = 0;
		int way = 1;
		card top = b[t++];

		if (top.v == 12) {
			way = -way;
		} else if (top.v == 7) {
			hand[who].pb(b[t++]); 
			hand[who].pb(b[t++]); 
			who = (who+way+p)%p;
		} else if (top.v == 1) {
			hand[who].pb(b[t++]); 
			who = (who+way+p)%p;
		} else if (top.v == 11) {
			who = (who+way+p)%p;
		}


		//cout << "=== " << endl;
		//cout << top.v << " " << top.n << endl;
		int ts = 0;
		while (true) {
			//if (t > n) cout << "AAAA" << endl;
			ts++;
			//cout << who << ": ";
			card mx({0,0});
			for (card c : hand[who]) {
				//cout << "(" << c.v << " " << c.n << ") ";
				if (c.v == top.v || c.n == top.n)
					mx = max(mx,c);
			}
			if (mx.v == 0) {
				hand[who].pb(b[t++]);
				for (card c : hand[who]) {
					if (c.v == top.v || c.n == top.n)
						mx = max(mx,c);
				}
			}

			for (int i = 0; i < hand[who].size(); i++) {
				if (hand[who][i] == mx) {
					top = mx;
					hand[who].erase(hand[who].begin() + i);
					break;
				}
			}
			//cout << top.v << " " << top.n << endl;

			if (hand[who].empty()) {
				printf("%d\n", who+1);
				break;
			}

			if (mx.v == 12) {
				way = -way;
			} else if (mx.v == 7) {
				who = (who+way+p)%p;
				hand[who].pb(b[t++]); 
				hand[who].pb(b[t++]); 
			} else if (mx.v == 1) {
				who = (who+way+p)%p;
				hand[who].pb(b[t++]); 
			} else if (mx.v == 11) {
				who = (who+way+p)%p;
			}
			who = (who+way+p)%p;
		}
	}
}
