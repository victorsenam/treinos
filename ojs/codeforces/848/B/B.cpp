#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int p[N], t[N];
int g[N];
int n, w, h;
int res[N][2], fin[N][2];

map<int, vector<int> > mp[2];
set<int> ts;

int main () {
	scanf("%d %d %d", &n, &w, &h);

	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &g[i], &p[i], &t[i]);
		g[i]--;

		int col = p[i] - t[i];

		if (g[i] == 0) {
			fin[i][0] = p[i];
			fin[i][1] = h;
		} else {
			fin[i][0] = w;
			fin[i][1] = p[i];
		}
		//printf("%d %d\n", fin[i][0], fin[i][1]);

		ts.insert(col);
		mp[g[i]][col].pb(i);
	}

	for (int tt : ts) {
		//printf("tt : %d\n", tt);
		vector<int> & a = mp[0][tt], b = mp[1][tt];

		sort(a.begin(), a.end(), [] (int i, int j) {
			return p[i] < p[j];
		});
		sort(b.begin(), b.end(), [] (int i, int j) {
			return p[i] < p[j];
		});

		for (int itt = 0; itt < 2; itt++) {
			for (int i = 0; i < a.size(); i++) {
				//printf("%d discover for %d(%d,%d) ", itt, i, p[i], t[i]);
				int j = i;
				if (a.size() - i - 1 >= b.size()) {
					//printf("parallel");
					j = a[i + b.size()];
				} else {
					//printf("ortogonal");
					j = b[a.size() - i - 1];
				}
				//printf(" %d(%d,%d)\n", j, p[j], t[j]);

				for (int k = 0; k < 2; k++)
					res[a[i]][k] = fin[j][k];
			}
			swap(a,b);
		}
	}

	for (int i = 0; i < n; i++) {
		printf("%d %d\n", res[i][0], res[i][1]);
	}
}
