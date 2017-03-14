#include <cstdio>
#include <climits>

int m, n, v[100];
int memo[50001];

int monta (int p) {
    int min, aux;

    if (p == 0) return 0;
    if (memo[p]) {
//        printf("memo[%d] == %d\n", p, memo[p]);
        return memo[p];
    }

    min = 50010;
    for (int i = 0; i < n; i++) {
        if (p >= v[i]) {
            aux = monta(p-v[i]) + 1;
//            printf("%d - %d = %d -> %d\n", p, v[i], p-v[i], aux);
            if (aux < min) min = aux;
        }
    }

    memo[p] = min;
    return min;
}

int main () {
    while(scanf("%d %d", &m, &n) != EOF && n && m) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
        }

        for (int i = 0; i <= m; i++) {
            memo[i] = 0;
        }
        
        monta(m);

        if (memo[m] >= 50010) printf("Impossivel\n");
        else printf("%d\n", memo[m]);
    }
}
