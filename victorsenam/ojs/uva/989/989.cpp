#include <bits/stdc++.h>

using namespace std;

const int N = 3;

int n;
int lins[N*N];
int cols[N*N];
int quas[N][N];
int mat[N*N][N*N];

bool bt (int i, int j) {
    if (i >= n*n)
        return 1;
    if (j >= n*n)
        return bt(i+1, 0);
    if (mat[i][j] != 0)
        return bt(i, j+1);
    
    for (int k = 1; k <= 9; k++) {
        if (lins[i]&(1<<k))
            continue;
        if (cols[j]&(1<<k))
            continue;
        if (quas[i/n][j/n]&(1<<k))
            continue;

        mat[i][j] = k;
        lins[i] |= (1<<k);
        cols[j] |= (1<<k);
        quas[i/n][j/n] |= (1<<k);
        if (bt(i, j+1))
            return 1;
        mat[i][j] = 0;
        lins[i] &= ~(1<<k);
        cols[j] &= ~(1<<k);
        quas[i/n][j/n] &= ~(1<<k);
    }
    return 0;
}

int main () {
    int ts = 0;
    while (scanf("%d", &n) != EOF && n) {
        if (ts++)
            printf("\n");
        memset(lins, 0, sizeof lins);
        memset(cols, 0, sizeof cols);
        memset(quas, 0, sizeof quas);
        for (int i = 0; i < n*n; i++) {
            for (int j = 0; j < n*n; j++) {
                scanf("%d", &mat[i][j]);
                if (mat[i][j]) {
                    lins[i] |= (1<<mat[i][j]);
                    cols[j] |= (1<<mat[i][j]);
                    quas[i/n][j/n] |= (1<<mat[i][j]);
                }
            }
        }

        if (bt(0, 0)) {
            for (int i =0 ; i < n*n; i++) {
                for (int j = 0; j < n*n; j++) {
                    if (j) printf(" ");
                    printf("%d", mat[i][j]);
                }
                printf("\n");
            }
        } else {
            printf("NO SOLUTION\n");
        }
    }
}
