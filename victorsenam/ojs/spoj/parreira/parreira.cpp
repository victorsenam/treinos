#include <bits/stdc++.h>

using namespace std;

#define N 500

int mat[N][N];
int n, m;
int lb, ub;
int t;
int maxT;
int lol, hil, loh, hih, midl, midh;

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n && m) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &mat[i][j]);

        scanf("%d", &t);
        while (t--) {
            scanf("%d %d", &lb, &ub);
            maxT = 0;

            for (int k = -n+1; k < m; k++) {
                lol = loh = max(0, -k);
                hil = hih = min(n, m-k);

    //            printf("%d: ", k);
    //            printf("%d-%d ", lo, hi);

                midl = midh = lol + (hil-lol)/2;
                while (lol < hil) {
                    if (mat[midl][k+midl] < lb) lol = midl+1;
                    else hil = midl;
                    midl = lol + (hil-lol)/2;
                }

                loh = midl;
                hih = min(loh + maxT + 1, hih);
                while (loh < hih) {
                    if (mat[midh][k+midh] <= ub) loh = midh+1;
                    else hih = midh;

                    midh = loh + (hih-loh)/2;
                }

                maxT = max(maxT, midh-midl);
            }

            printf("%d\n", maxT);
        }
        printf("-\n");
    }
}
