
#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 53;

const int mv[4][2] = {
	{0,1}, {1,0}, {-1,0}, {0,-1}
};

char mat[N][N];
int p[4];
int cnt;
char str[200];
int n, m;

int main () {
	scanf("%d %d", &n, &m);

	int si, sj;
	for (int i = 0; i < n; i++) {
		scanf(" %s", mat[i]);
		for (int j = 0; j < m; j++)
			if (mat[i][j] == 'S') {
				si = i;
				sj = j;
			}
	}
	scanf(" %s", str);

	for (int i = 0; i < 4; i++)
		p[i] = i;

	do {
		int i = si, j = sj;

		bool ex = 0;
		for (int k = 0; !ex && str[k]; k++) {
			i += mv[p[str[k]-'0']][0]; j += mv[p[str[k]-'0']][1];
			if (i >= n || i < 0 || j >= m || j < 0 || mat[i][j] == '#')
				break;
			else if (mat[i][j] == 'E')
				ex = 1;
		}

		cnt += ex;
	} while (next_permutation(p, p+4));

	printf("%d\n", cnt);
}
