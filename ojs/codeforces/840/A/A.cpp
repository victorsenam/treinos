#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int a[2][N], p[2][N];
int n;
int r[N];

int main () {
	scanf("%d", &n);

	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[k][i]);
			p[k][i] = i;
		}

		sort(p[k], p[k]+n, [k] (int i, int j) {
			return a[k][i] < a[k][j];
		});
	}

	for (int i = 0; i < n; i++) {
		r[p[1][n-i-1]] = a[0][p[0][i]];
	}

	for (int i = 0; i < n; i++)
		printf("%d ", r[i]);
	printf("\n");
}
