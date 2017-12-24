#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
const int mv[4][2] = {
	{0,1},{1,0},{0,-1},{-1,0}
};

int n, m;
char ts[5];
int mat[N];
int app[N];

int main () {
	scanf("%s", ts);
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n*m; i++) {
		scanf("%d", &mat[i]);
		mat[i]--;
		app[mat[i]]++;
	}
	for (int i = 0; i < n*m; i++)
		if (app[mat[i]] != 1) printf("AAA\n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 4; k++) {
				int ni = (i+mv[k][0]);
				int nj = (j+mv[k][1]);
				if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
				int d = abs(mat[i*m+j]/m - mat[ni*m+nj]/m) + abs(mat[i*m+j]%m - mat[ni*m+nj]%m);
				if (d <= 1) printf("Errou %d %d: %d %d\n", i, j, mat[i*m+j], mat[ni*m+nj]);
			}
		}
	}
	printf("Fim\n");
}
