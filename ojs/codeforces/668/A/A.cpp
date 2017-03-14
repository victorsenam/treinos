#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 107;
const int M = 10007;

int mat[N][N];
int query[M][4];

int n, m, q;

int main () {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &query[i][0]);
        scanf("%d", &query[i][1]);
        query[i][1]--;
        if (query[i][0] == 3) {
            scanf("%d %d", &query[i][2], &query[i][3]);
            query[i][2]--;
        }
    }

    for (int i = q-1; i >= 0; i--) {
        if (query[i][0] == 1) {
            int l = query[i][1];
            int aux = mat[l][m-1];
            for (int i = m-1; i >= 1; i--)
                mat[l][i] = mat[l][i-1];
            mat[l][0] = aux;
        } else if (query[i][0] == 2) {
            int c = query[i][1];
            int aux = mat[n-1][c];
            for (int i = n-1; i >= 1; i--)
                mat[i][c] = mat[i-1][c];
            mat[0][c] = aux;
        } else {
            mat[query[i][1]][query[i][2]] = query[i][3];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                DEBUG("%d ", mat[i][j]);
            }
            DEBUG("\n");
        }
        DEBUG("\n\n");
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
