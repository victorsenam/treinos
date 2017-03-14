#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 151;
const int K = 30;
const int D = 8;

const int  mv[8][2] = {
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1}
};

int visi[N][2*N][K];
bitset<2*N*N*N> ok;
int v[K], n;

void move (int i, int j, int x, int d) {
    i += mv[d][0]*x;
    j += mv[d][1]*x;
    if (i < 0) i = -i;
        //printf("%d %d\n", i, j);
    if (!ok[i*2*N + j + N]) {
        ok[i*2*N + j + N] = 1;
    }
}

void pd (int i, int j, int k, int d) {
    if (k >= n)
        return;
    if (i < 0) {
        i = -i;
        if (d == 7) d = 1;
        if (d == 6) d = 2;
        if (d == 5) d= 3;
    }
    while (d < 0)
        d += 8;
    while (d >= 8)
        d -= 8;

    if (visi[i][j+N][k]&(1<<d))
        return;
    visi[i][j+N][k] |= (1<<d);

    for (int x = 1; x <= v[k]; x++) {
        move(i, j, x, d);
    }
    pd(i+mv[d][0]*v[k], j+mv[d][1]*v[k], k+1, d-1);
    pd(i+mv[d][0]*v[k], j+mv[d][1]*v[k], k+1, d+1);
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    pd(0, 0, 0, 0);

    int res = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < 2*N; j++)
            if (ok[i*2*N + j]) {
                res += 1 + (i!=0);
            }

    printf("%d\n", res);
}
