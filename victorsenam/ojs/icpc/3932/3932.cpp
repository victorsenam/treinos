#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 307;

char mat[N][N];
int acc[N][N];
int n, m;
int qt;
int mini[N];

inline int get (int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) return 0;
    return acc[i][j];
}

inline int getres (int i, int j, int mid, int k) {
    return get(i, j) - get(i, k-1) - get(mid-1, j) + get(mid-1, k-1);
}

int main () {
    while (scanf("%d %d %d", &n, &m, &qt) != EOF && n) {
        for (int i = 0; i < n; i++)
            scanf(" %s", mat[i]);

        int res = INT_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                acc[i][j] = get(i-1, j) + get(i, j-1) - get(i-1, j-1) + (mat[i][j] == '.');

                for (int k = 0; k <= j; k++) {

                    while (mini[k] < i && getres(i, j, mini[k]+1, k) >= qt)
                        mini[k]++; 

                    if (getres(i, j, mini[k], k) >= qt)
                        res = min(res, (i-mini[k]+1)*(j-k+1));
                }
            }

            for (int j = 0; j < m; j++)
                mini[j] = 0;
        }

        printf("%d\n", res);
    }
}
