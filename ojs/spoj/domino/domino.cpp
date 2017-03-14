#include <bits/stdc++.h>

using namespace std;

int pecas[7][8], vals[7][8];
char usadas[28];
int possi, t;

int getpeca(int a, int b) {
    int m, n;
    m = min(a,b);
    n = max(a,b);
    return 7*m - m*(m+1)/2 + n + 1;
}

void printmat(int mat[7][8]) {
    for (int i = 0; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void btrack(int x, int y) {
    int v;
    if (x >= 7) {
        possi++;
    } else if (y >= 8) {
        btrack(x+1, 0);
    } else if (pecas[x][y]) {
        btrack(x, y+1);
    } else {
        if (x+1 < 7) {
            v = getpeca(vals[x][y], vals[x+1][y]);

            if (!usadas[v-1] && !pecas[x+1][y]) {
                usadas[v-1] = 1;
                pecas[x][y] = pecas[x+1][y] = v;
                btrack(x, y+1);
                pecas[x][y] = pecas[x+1][y] = 0;
                usadas[v-1] = 0;
            } else {
            }
        } else {
        }
        if (y+1 < 8) {
            v = getpeca(vals[x][y], vals[x][y+1]);

            if (!usadas[v-1] && !pecas[x][y+1]) {
                usadas[v-1] = 1;
                pecas[x][y] = pecas[x][y+1] = v;
                btrack(x, y+1);
                pecas[x][y] = pecas[x][y+1] = 0;
                usadas[v-1] = 0;
            } else {
            }
        } else {
        }
    }
}

int main () {
    scanf("%d", &t);
    int ts = 0;
    while (t--) {
        ts++;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 8; j++) {
                scanf("%d", &vals[i][j]);
                pecas[i][j] = 0;
            }
        }


        for (int i = 0; i < 28; i++) {
            usadas[i] = 0;
        }

        possi = 0;
        btrack(0, 0);
        printf("Teste %d\n", ts);
        printf("%d\n\n", possi);
    }
}
