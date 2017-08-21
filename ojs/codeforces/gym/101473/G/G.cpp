#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;

int n, m;
int a[N][N];
int v[N];

int countcyc (int n) {
	int rs = 0;
	for (int i = 0; i < n; i++) {
		int j = i;
		int pr = 0;
		while (v[j] != -1) {
			pr++;
			int nx = v[j];
			v[j] = -1;
			j = nx;
		}
		if (pr)
			rs += pr-1;
	}
	return rs;
}

int main () {
	scanf("%d %d", &n, &m);

	bool ok = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &a[i][j]);
			a[i][j]--;

			ok &= ((a[i][j]/m) == (a[i][0]/m));
			ok &= ((a[i][j]%m) == (a[0][j]%m));
		}
	}

	if (!ok) {
		printf("*\n");
		return 0;
	}

	int rs = 0;
	for (int i = 0; i < n; i++)
		v[i] = (a[i][0]/m);
	rs += countcyc(n);
	for (int i = 0; i < m; i++)
		v[i] = (a[0][i]%m);
	rs += countcyc(m);
	printf("%d\n", rs);
}
