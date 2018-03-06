#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 303;

int n, m;
char mat[5][N][N];

bool get (int a, int i, int j) {
	bool r = 0;
	for (int x = -1; x <= 1; x++) for (int y = -1; y <= 1; y++)
		if (i + x >= 0 && i + x < n && j + y >= 0 && j + y < m && mat[a][i+x][j+y])
			r = !r;
	return r;
}

int go1 (int a, int b) {
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) mat[b][i][j] = 0;

	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < m-1; j++) {
			mat[b][i][j] = 0;
			mat[b][i][j] = (get(b,i-1,j-1) != mat[a][i-1][j-1]);
		}
	}

	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (get(b,i,j) != mat[a][i][j]) return i;
	return -1;
}

int go2 (int a, int b) {
	for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) mat[b][i][j] = 0;
	for (int j = 1; j < m-1; j++) {
		for (int i = 1; i < n-1; i++) {
			mat[b][i][j] = 0;
			mat[b][i][j] = (get(b,i-1,j-1) != mat[a][i-1][j-1]);
		}
	}

	for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) if (get(b,i,j) != mat[a][i][j]) return j;
	return -1;
}

int main () {
	scanf("%d %d", &m, &n);

	for (int i = 0; i < n; i++) {
		scanf(" %s", mat[0][i]);
		for (int j = 0; j < m; j++) mat[0][i][j] = (mat[0][i][j] == '#');
	}

	while (n > 2 && m > 2) {
		int l = go1(0,1);
		int c = go2(0,2);

		if (c != -1) {
			mat[0][l][c] ^= 1;
			int r = go1(0,1);
			if (r != -1) { mat[0][l][c] ^= 1; break; }
		}

		for (; n > 0; n--) {
			bool ok = 1;
			for (int j = 0; j < m && ok; j++) if (mat[1][n-1][j]) ok = 0;
			if (!ok) break;
		}
		for (; m > 0; m--) {
			bool ok = 1;
			for (int i = 0; i < n && ok; i++) if (mat[1][i][m-1]) ok = 0;
			if (!ok) break;
		}

		for (l = 0; l < n; l++) {
			bool ok = 1;
			for (int j = 0; j < m; j++) if (mat[1][l][j]) ok = 0;
			if (!ok) break;
		}

		for (c = 0; c < m; c++) {
			bool ok = 1;
			for (int i = 0; i < n; i++) if (mat[1][i][c]) ok = 0;
			if (!ok) break;
		}

		for (int i = 0; i < n - l; i++) {
			for (int j = 0; j < m - c; j++) {
				mat[0][i][j] = mat[1][i+l][j+c];
			}
		}
		n-=l; m -= c;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) 
			printf("%c", mat[0][i][j]?'#':'.');
		printf("\n");
	}
}
