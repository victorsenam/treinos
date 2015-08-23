#include <cstdio>
#include <climits>

#define MAX 1001

int v[MAX][MAX], t, n, m;
long long int memo[MAX][MAX], maxi, aux, row, col;
char u[MAX][MAX];

long long int calc (int r, int c) {
    if (r >= n || c >= m || r < 0 || c < 0) return 0;
    if (!u[r][c]) {
        u[r][c] = 1;
        memo[r][c] = v[r][c] + calc(r+1, c) + calc(r, c+1) - calc(r+1, c+1);
    }

    return memo[r][c];
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &v[i][j]);
                u[i][j] = 0;
            }
        }

        maxi = LLONG_MIN;

        calc(0, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (memo[i][j] > maxi) maxi = memo[i][j];
            }
        }

        printf("%lld\n", maxi);

/*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (u[i][j]) printf("%+04lld ", memo[i][j]);
                else printf("     ");
            }
            printf("\n");
        }
*/
    }
}
