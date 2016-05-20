#include <bits/stdc++.h>

using namespace std;

const int N = 107;

bool memo[N][N];
int visi[N][N], turn;
char sta[N];
char fimzinho[N];
int n;
int k;

bool pd (int i, int j) {
	if (i + j == n) return 1;
	if (visi[i][j] == turn)
		return memo[i][j];
	visi[i][j] = turn;

	bool & me = memo[i][j];
	me = 0;

	if (k-1-i >= 0 && fimzinho[k-1-i] == sta[i+j]) me = pd(i+1, j);
	if (k+j < n && !me && fimzinho[k+j] == sta[i+j]) me = pd(i, j+1);
	return me;
}

int main ( ){
	scanf(" %s %s", sta, fimzinho);
	n = strlen(sta);
	++turn;

	for (k = 0; k < n; k++) {
		++turn;
		if (pd(0,0)) {
			printf("S\n");
			return 0;
		}
	}
	printf("N\n");
}
