#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int M = 107;

const int mk[2][8] = {
	{2, 2, 1, 1, -1, -1, -2, -2},
	{1, -1, 2, -2, 2, -2, 1, -1}
};

const int mq[2][8] = {
	{-1, -1, -1, 0, 0, 1, 1, 1},
	{-1, 0, 1, -1, 1, -1, 0, 1}
};

int n, m;
int qtd[3];
int pos[3][M][2];
int mat[N][N];
int a, b;

int main () {
	int tt = 0;
	while ( scanf("%d %d", &n, &m) != EOF && (n || m)) {
		for (int i = 0; i < 3; i++) {
			scanf("%d", qtd+i);
			for (int j = 0; j < qtd[i]; j++) {
				scanf("%d %d", &pos[i][j][0], &pos[i][j][1]);
				pos[i][j][0]--;
				pos[i][j][1]--;
				mat[pos[i][j][0]][pos[i][j][1]] = 2;
			}
		}

		for (int i = 0; i < qtd[0]; i++) {
			for (int j = 0; j < 8; j++) {
				for (int k = 1; ; k++) {
					int pi = pos[0][i][0] + k*mq[0][j];
					int pj = pos[0][i][1] + k*mq[1][j];
					
					if (pi < 0 || pi >= n || pj < 0 || pj >= m || mat[pi][pj] == 2)
						break;
					mat[pi][pj] = 1;
				}
			}
		}

		for (int i = 0; i < qtd[1]; i++) {
			for (int j = 0; j < 8; j++) {
				int pi = pos[1][i][0] + mk[0][j];
				int pj = pos[1][i][1] + mk[1][j];
				
				if (pi < 0 || pi >= n || pj < 0 || pj >= m)
					continue;
				mat[pi][pj] = 1;
			}
		}
		
		int res = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				//printf("%d", mat[i][j]);
				if (mat[i][j] == 0)
					res++;
				mat[i][j] = 0;
			}
			//printf("\n");
		}
		printf("Board %d has %d safe squares.\n", ++tt, res);
	}
}
