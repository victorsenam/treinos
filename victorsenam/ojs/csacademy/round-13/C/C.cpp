#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 5e4+7;

int ts, n;
int v[2][N];
int p[2][N];
int r[N];
int kk;

int cmp_t (int i, int j) {
    return v[kk][i] < v[kk][j];
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d", &n);

        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < n; i++) {
                scanf("%d", &v[k][i]);
                p[k][i] = i;
            }

            kk = k;
            sort(p[k], p[k]+n, cmp_t);
        }

        bool ok = 1;
        for (int k = 0; ok && k < 2; k++)
            for (int i = 0; ok && i < n/2; i++)
                if (v[k][p[k][i]] >= v[!k][p[!k][n/2+i]])
                    ok = 0;

        if (!ok) {
            printf("-1\n");
            continue;
        }

        for (int i = 0; i < n/2; i++)
            r[p[0][i]] = p[1][(n/2)+i];
        for (int i = n/2; i < n; i++)
            r[p[0][i]] = p[1][i-(n/2)];
        for (int i = 0; i < n; i++)
            printf("%d ", r[i]+1);
        printf("\n");
    }

}
