#include <bits/stdc++.h>

using namespace std;

#define N 101

int cols[N], lin, max_col, max_lin, aux, n, m;

int main () {
    scanf("%d %d", &n, &m);
    max_col = max_lin = 0;
    for (int i = 0; i < n; i++) {
        lin = 0;
        for (int j = 0; j < m; j++) {
            if (!i) cols[j] = 0;
            scanf("%d", &aux);
            cols[j] += aux;
            lin += aux;
            if (i == n-1 && cols[j] > max_col) max_col = cols[j];
        }
        if (lin > max_lin) max_lin = lin;
    }

    printf("%d\n", max(max_col, max_lin));
}
