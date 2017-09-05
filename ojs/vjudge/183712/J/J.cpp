#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e2+7;
const int S = 52;

struct node {
	int i, j;
	ll d;

	bool operator < (const node & ot) const {
		return d > ot.d;
	}
};

int dist[N][S];
bool visi[N][S];
char str[N][S];
int n;

int main () {
	while (scanf("%d", &n) && n) {
		priority_queue<node> qu;
		for (int i = 0; i < n; i++) {
			scanf(" %s", str[i]);
			for (int j = 0; !j || str[i][j-1]; j++) {
				dist[i][j] = INT_MAX;
				visi[i][j] = 0;
			}
			dist[i][0] = 0;
			qu.push(node({i,0,0}));
		}

		int res = -1;
		while (!qu.empty()) {
			node att = qu.top();
			qu.pop();


			if (visi[att.i][att.j]) continue;
			visi[att.i][att.j] = 1;

			if (!str[att.i][att.j]) {
				res = dist[att.i][att.j];
				break;
			}

			for (int i = 0; i < n; i++) {
				if (att.j == 0 && i == att.i) continue;
				bool ok = 1;
				int k;
				for (k = 0; ok && str[i][k] && str[att.i][att.j+k]; k++)
					ok = (str[i][k] == str[att.i][att.j+k]);
				if (!ok) continue;
				
				node nxt = att;
				if (str[i][k]) {
					nxt.i = i;
					nxt.j = k;
				} else {
					nxt.i = att.i;
					nxt.j = att.j + k;
				}
				nxt.d += k;
				if (dist[nxt.i][nxt.j] <= nxt.d) continue;
				dist[nxt.i][nxt.j] = nxt.d;
				qu.push(nxt);
			}
		}

		printf("%d\n", res);
	}
}
