#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

//const int N = 1e3+7;
const int N = 7;
const int M = N+3;

char inp[M], aa[M];
int val[M][M], req;
int p[M][M], q[M][M];
int acc[M][M][10];
int cst[M][M][10];
int still;
int ln[M];
int inv[M][M];
int iln;
int c[M];
ll memo[M][M][3];
int n;

void printa (int k, int j) {
    printf("%d[", j);
    for (int i = k; i < N; i++)
        printf("%d", val[j][i]);
    printf("] ");
}

ll pd (int i, int cr, int zr) {
    if (i <= 0 || (!cr && i < still)) {
        if (!zr && req)
            return LLONG_MAX;
        else
            return cr * c[1];
    }

    ll & me = memo[i][cr][zr];
    if (me != -1)
        return me;

    int llim = 0;
    int rlim = 9;

    if (aa[i] != '?')
        llim = rlim = aa[i]-'0';

    me = 0;
    int dd = -1;
    int nn = -1;
    int zz = -1;
    for (int k = llim; k <= rlim; k++) {
        int ncr = 0;
        ncr += acc[i][n][max(0, 10-k-1)] - acc[i][n-cr][max(0, 10-k-1)];
        ncr += acc[i][n-cr][10-k];

        int nzr = zr;
        if (llim != rlim) {
            if (k)
                nzr = 2;
            else if (zr)
                nzr = 1;
            else
                nzr = 0;
        }

        ll loc = pd(i-1, ncr, nzr);
        if (loc == LLONG_MAX) continue;
        loc += cst[i][n][(k+1)%10] - cst[i][n-cr][(k+1)%10];
        loc += cst[i][n-cr][k];
        if (k == 0 && i + iln < N) {
            loc -= inv[i][n-cr]*c[0];
        }

        me = max(me, loc);
        if (me == loc) {
            dd = k;
            nn = ncr;
            zz = nzr;
        }
    }

    printf("%d %d %d [use %d] %d %d %d [get %lld]\n", i, cr, zr, dd, i-1, nn, zz, me);
    return me;
}

void builda () {
    if (inp[0] == '?')
        req = 1;
    int m = strlen(inp);
    iln = m;
    for (int j = 0; inp[j]; j++) {
        aa[N-m+j] = inp[j];
    }
    still = min(still, N-m);
    for (int j = 0; j < N-m; j++)
        aa[j] = '0';
}

int main () {
    memset(memo, -1, sizeof memo);
    still = N;
    scanf(" %s", inp);
    builda();
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf(" %s", inp);
        int m = strlen(inp);
        ln[i] = m;
        for (int j = 0; inp[j]; j++)
            val[i][N-m+j] = inp[j]-'0';
        still = min(still, N-m);
    }

    for (int i = 0; i < 10; i++)
        scanf("%d", &c[i]);

    for (int k = N-1; k >= 0; k--) {
        //debug("=== %d \n", k);

        for (int j = 0; j < n; j++)
            p[k][j] = j;

        sort(p[k], p[k]+n, [k] (int i, int j) {
            if (val[i][k+1] != val[j][k+1])
                return val[i][k+1] < val[j][k+1];
            return q[k+1][i] < q[k+1][j];
        });

        for (int _j = 0; _j < n; _j++) {
            int j = p[k][_j];
            //printa(k,j);

            q[k][j] = _j;

            for (int d = 0; d < 10; d++)
                acc[k][_j+1][d] = acc[k][_j][d];
            acc[k][_j+1][val[j][k]]++;

            for (int d = 8; d >= 0; d--)
                acc[k][_j+1][d] += acc[k][_j+1][d+1];
        }
        //debug("\n");

        for (int _j = 0; _j < n; _j++) {
            int j = p[k][_j];
            for (int d = 0; d < 10; d++) {
                cst[k][_j+1][d] = cst[k][_j][d];
                cst[k][_j+1][d] += c[(val[j][k]+d)%10];
            }
            inv[k][_j+1] = inv[k][_j];
            if (ln[j] + k < N)
                inv[k][_j+1]++;
        }
    }

    printf("%lld\n", pd(N-1, 0, 0));
}
