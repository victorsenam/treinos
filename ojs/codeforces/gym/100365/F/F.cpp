#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 53;

int v[N][N];
char x[N][N];
int s[N*N];

int n, m;

int res;
void go (int x, int a, int b, int i, int j) {
	if (res != x) return;
	printf("%d %d\n%d %d\n", i+1, j+1, a+1, b+1);
	exit(0);
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("coins.in", "r", stdin);
	freopen("coins.out", "w", stdout);
#endif
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int a = 0; a < i; a++)
				s[v[a][j]] = i*n + j + 1;
			for (int b = 0; b < j; b++)
				s[v[i][b]] = i*n + j + 1;
			for (int a = 0; a < i; a++)
				for (int b = 0; b < j; b++)
					s[(v[a][j]^v[i][b]^v[a][b])] = i*n + j + 1;

			v[i][j] = 1;
			while (s[v[i][j]] == i*n + j + 1)
				v[i][j]++;

			scanf(" %c", &x[i][j]);
			x[i][j] -= '0';
			if (x[i][j])
				res ^= v[i][j];

		}
	}

	if (res) {
		printf("Ann\n");

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (!x[i][j]) continue;
				go(v[i][j], -1, -1, i, j);
				for (int a = 0; a < i; a++)
					go(v[a][j]^v[i][j], a, -1, i, j);
				for (int b = 0; b < j; b++)
					go(v[i][b]^v[i][j], -1, b, i, j);
				for (int a = 0; a < i; a++) {
					for (int b = 0; b < j; b++) {
						go(v[a][b]^v[a][j]^v[i][b]^v[i][j], a, b, i, j);
					}
				}
			}
		}
	} else {
		printf("Betty\n");
	}
}
