#include <bits/stdc++.h>

using namespace std;

const int N = 52;
const int mi[4] = {0, 0, -1, 1};
const int mj[4] = {1, -1, 0, 0};

int turn;
int vis[N][N];
char mat[N][N];
int n, m;

int dfs (int i, int j) {
	if (vis[i][j] == turn)
		return 0;
	
	vis[i][j] = turn;

	if (mat[i][j] == '#' || mat[i][j] == 'T')
		return 0;

	int res = 0;
	if (mat[i][j] == 'G')
		res = 1;
	
		for (int k = 0; k < 4; k++)
		if (mat[i+mi[k]][j+mj[k]] == 'T')
			return res;
	for (int k = 0; k < 4; k++)
		res += dfs(i+mi[k], j+mj[k]);
	return res;
}

int main () {
	while (scanf("%d %d", &m, &n) != EOF) {
		turn++;
		for (int i = 0; i < n; i++)
			scanf(" %s", mat[i]);
		
		int res = -1;
		for (int i = 0; i < n && res == -1; i++) {
			for (int j = 0; j < m && res == -1; j++) {
				if (mat[i][j] == 'P')
					res = dfs(i, j);
			}
		}
		printf("%d\n", res);
	}
}
