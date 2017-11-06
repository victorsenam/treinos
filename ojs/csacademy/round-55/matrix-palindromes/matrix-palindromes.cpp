#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n, m, k;
string mat[N];
int cost[N];
char str[N];

int fr[500];

int main () {
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 0; i < n; i++) {
		scanf(" %s", str);
		mat[i] = str;
	}

	int res = 0;

	for (int i = 0; i < n && n - i - 1 >= i; i++) {
		for (int j = 0; j < m && m - j - 1 >= j; j++) {
			int need = (mat[i][j] != mat[i][m-j-1]) + (i != n-i-1 && mat[n-i-1][j] != mat[n-i-1][m-j-1]);
			if (j == m-j-1)
				need = 0;
			res += need;

			set<pii> s;
			s.insert(pii(i,j));
			s.insert(pii(i,m-j-1));
			s.insert(pii(n-i-1,j));
			s.insert(pii(n-i-1,m-j-1));

			int mx = 0;
			for (pii p : s) {
				fr[mat[p.first][p.second]]++;
				mx = max(mx, fr[mat[p.first][p.second]]);
			}

			cout << i << " " << j << " needs " << need << " can be " << s.size() - mx << endl;
			cost[j] += s.size() - mx - need;

			for (pii p : s) {
				fr[mat[p.first][p.second]]--;
				mx = max(mx, fr[mat[p.first][p.second]]);
			}
		}
	}

	sort(cost, cost + m/2);
	for (int i = 0; i < k/2; i++)
		res += cost[i];

	if (k&1) {
		int mn = cost[k/2];
		if (m&1)
			mn = min(mn,cost[m/2]);
		res += mn;
	}
	printf("%d\n", res);
}
