#include <bits/stdc++.h>

using namespace std;

const int N = 8;
const int mi[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int mj[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool mat[N][N];
int ti[N][N];
int tj[N][N];
int n;
int ai, aj;
int turn;

bool bt(int i, int j, int c) {
	if (i < 0 || i >= n)
		return 0;
	if (j < 0 || j >= n)
		return 0;

	if (mat[i][j]) {
		if (c == n*n+1)
			return 1;
        else
			return 0;
	}
	
	mat[i][j] = 1;
	for (int k = 0; k < 8; k++) {
		if (bt(i+mi[k], j+mj[k], c+1)) {
            if (c == n*n) {
                ai = i;
                aj = j;
            }
			ti[i][j] = i+mi[k];
			tj[i][j] = j+mj[k];
			return 1;
		}
	}
	mat[i][j] = 0;
	return 0;
}

void printmat(int i, int j) {
	printf("%c%d\n", 'a'+i, j+1);

	if (ai == i && aj == j)
		return;
	
	printmat(ti[i][j], tj[i][j]);
}

int main () { 
    scanf("%d", &n);
    
    if (n == 1)
        printf("a1\n");
    else if (bt(0, 0, 1))
        printmat(0, 0);
    else
        printf("IMPOSSIBLE\n");
}
