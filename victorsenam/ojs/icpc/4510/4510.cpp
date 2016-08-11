#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef double db;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1007;
const db eps = -1e-9;

int n;
db cd[N][3];
int visi[N][2], turn;
db memo[N][2];

inline db sq (db x)
{ return x*x; }
inline db dist (db xa, db ya, db xb, db yb)
{ return sqrt(sq(xa-xb)+sq(ya-yb)); }
db triang (db piv, db h, db curr, db a, db b, db lim) {
    a = h - a;
    b = h - b;
    db c = piv - curr;
    db r = piv - b*c/a;
    
    if (r - piv < eps)
        return min(r, lim);
    return max(r, lim);
}

db pd (int i, bool s) {
    db & me = memo[i][s];
    if (visi[i][s] == turn) return me;
    visi[i][s] = turn;
    me = 1./0.;

    if (i == n-1) {
        me = abs(cd[i][0] - cd[n][0]);
    }

    db lo = cd[i+1][1];
    db hi = cd[i+1][2];

    int j;
    for (j = i+1; j < n && lo - hi < -eps && lo - cd[j][2] < -eps && cd[j][1] - hi < -eps; j++) {
        if (lo - cd[j][1] < -eps) {
            DEBUG("(%d,%d) pra (%d,%d)\n", i, s, j, 0);
            me = min(me, pd(j, 0) + dist(cd[i][1+s], cd[i][0], cd[j][1], cd[j][0]));
        }
        if (cd[j][2] - hi < -eps) {
            DEBUG("(%d,%d) pra (%d,%d)\n", i, s, j, 1);
            me = min(me, pd(j, 1) + dist(cd[i][1+s], cd[i][0], cd[j][2], cd[j][0]));
        }

        lo = triang(cd[i][1+s], cd[i][0], lo, cd[j][0], cd[j+1][0], cd[j+1][1]);
        hi = triang(cd[i][1+s], cd[i][0], hi, cd[j][0], cd[j+1][0], cd[j+1][2]);
    }

    if (j == n && lo - hi < -eps && lo - cd[j][2] < -eps && cd[j][1] - hi < -eps) {
        DEBUG("(%d,%d) pro final [%.2f,%.2f]\n", i, s, max(lo, cd[n][1]), min(hi, cd[n][2]));
        me = min(me, dist(cd[i][1+s], cd[i][0], max(lo, cd[n][1]), cd[n][0]));
        me = min(me, dist(cd[i][1+s], cd[i][0], min(hi, cd[n][2]), cd[n][0]));
    }

    return me;
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        turn++;
        scanf("%lf %lf", &cd[0][1], &cd[0][0]);
        db ref = cd[0][0];

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 3; j++)
                scanf("%lf", &cd[i][j]);
        }

        printf("%.20f\n", pd(0, 0));
    }
}
