#include <bits/stdc++.h>

using namespace std;

const int N = 300;
const char let[4] = {'^', '<', '>', 'v'};
const int mov[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };

char mat[N][N];
char str[N];
int n, m;
int visi[N][N][N], turn;
int ls[3], att[3];
int cic[N*N*N][2], rs;

void dfs (int i, int j, int k) {
	if (visi[i][j][k] == turn) {
		ls[0] = i; ls[1] = j; ls[2] = k;
		return;
	}
	
	int c = 0;
	while (let[c] != str[k]) c++;

	if (mat[i+mov[c][0]][j+mov[c][1]] != '#') dfs(i+mov[c][0], j+mov[c][1], (k+1)%m);
	else dfs(i, j, (k+1)%m);
}

int main () {
	while (scanf("%d", &n) != EOF) {
		scanf(" %s", str);
		m = strlen(str);
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf(" %c", &mat[i][j]);
				if (mat[i][j] == 'R') {
					att[0] = i;
					att[1] = j;
					att[2] = 0;
				}
			}
		}

		++turn;
		while (visi[att[0]][att[1]][att[2]] != turn) {
			int & i = att[0]; int & j = att[1]; int & k = att[2];
			visi[i][j][k] = turn;

			int c = 0;
			while (let[c] != str[k]) c++;

			if (mat[i+mov[c][0]][j+mov[c][1]] != '#') {
				i += mov[c][0];
				j += mov[c][1];
			}

			k = (k+1)%m;
		}
		for (int i = 0; i < 3; i++)
			ls[i] = att[i];

		rs = 0;
		do {
			int & i = att[0]; int & j = att[1]; int & k = att[2];
			cic[rs][0] = i; cic[rs][1] = j;
			if (rs && cic[rs][0] == cic[rs-1][0] && cic[rs][1] == cic[rs-1][1]) rs--;
			rs++;

			int c = 0;
			while (let[c] != str[k]) c++;

			if (mat[i+mov[c][0]][j+mov[c][1]] != '#') {
				i += mov[c][0];
				j += mov[c][1];
			}

			k = (k+1)%m;
		} while (att[0] != ls[0] || att[1] != ls[1] || att[2] != ls[2]);
		while (rs > 1 && cic[0][0] == cic[rs-1][0] && cic[0][1] == cic[rs-1][1]) rs--;
			
		int d = 1;
		for (; d <= rs; d++) {
			if (rs%d) continue;
			int i = 0;
			for (i = 0; i + d < rs && cic[i][0] == cic[i+d][0] && cic[i][1] == cic[i+d][1]; i++);
			if (i + d == rs) break;
		}
		printf("%d\n", d);
	}
}
