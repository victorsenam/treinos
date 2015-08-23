#include <bits/stdc++.h>

using namespace std;

#define N 1001

int n, k, v;
unsigned int m[N][N], s[N], aux;

int main () {
    while (scanf("%d %d", &n, &k) != EOF && n) {
        s[n] = 0;
        for (int i = n-1; i >= 0; i--) {
            scanf("%d", &aux);
            s[i] = s[i+1] + aux;
            printf("%d ", s[i]);
        }
        printf("\n");

        for (int i = 0; i <= k; i++) m[n][i] = 0;
        for (int i = n-1; i >= 0; i--) printf("%d ", m[i][0] = m[i+1][0] + (s[i]-s[i+1])*s[i+1]);
        printf("\n");

        for (int i = n-1; i>= 0; i--) {
            for (int j = 1; j <= k; j++) {
                v = m[i][j] = m[i][0];
                for (int b = n-1; b > i; b--) {
                    v -= s[b+1]*(s[b]-s[b+1]); // Isso está errado! Acho que estou fazendo na ordem errada...
                    m[i][j] = min(m[i][j], v+m[b][j-1]);
                }
                printf("%d %d -> %d\n", i, j, m[i][j]);
            }
        }

        printf("%d\n", m[n][k]);
    }
}
