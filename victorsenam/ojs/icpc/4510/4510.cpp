#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef double db;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1007;
const db eps = 1e-9;

int n;
db cd[N][3];
int visi[N][2], turn;
db memo[N][2], lo, hi;

inline db sq (db x)
{ return x*x; }
inline db dist (db xa, db ya, db xb, db yb)
{ return sqrt(sq(xa-xb)+sq(ya-yb)); }

db triang (db x1, db y1, db x2, db y2, db x3, db y3) {
    db a = x2-x1;
    db b = y2-y1;

    if (b < eps) return x3;

    db d = y3-y1;

    db c = (d*a/b);
    db r = x1 - c;

    if (fabs(r-x1) > fabs(x1-x3)) return x3;
    return r;
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        turn++;
        scanf("%lf %lf", &cd[0][1], &cd[0][0]);
        db ref = cd[0][0];

        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 3; j++)
                scanf("%lf", &cd[i][j]);

        for (int i = n-1; i >= 0; i--) {
            for (int s = 0; s < 2; s++) {
                db & me = memo[i][s];
                me = 1./0.;

                lo = cd[i+1][1+s];
                hi = cd[i+1][1+s];

                int j;
                for (j = i+1; j <= n && lo <= cd[j][2] && cd[j][1] <= hi; j++) {
                    if (lo <= cd[j][1])
                        me = min(me, memo[j][0] + dist(cd[i][1+s], cd[i][0], cd[j][1], cd[j][0]));
                    if (cd[j][2] <= hi)
                        me = min(me, memo[j][1] + dist(cd[i][1+s], cd[i][0], cd[j][2], cd[j][0]));

                    lo = triang(cd[i][1+s], cd[i][0], lo, cd[j-1][0], cd[j][1], cd[j][0]);
                    hi = triang(cd[i][1+s], cd[i][0], hi, cd[j-1][0], cd[j][2], cd[j][0]);
                }

                if (j == n+1 && lo <= hi) {
                    me = min(me, dist(cd[i][1+s], cd[i][0], lo, cd[n][0]));
                    me = min(me, dist(cd[i][1+s], cd[i][0], hi, cd[n][0]));
                    if (lo <= cd[i][1+s] && cd[i][1+s] <= hi)
                        me = min(me, abs(cd[i][0] - cd[n][0]));
                }
            }
        }

        printf("%.20f\n", memo[0][0]);
    }
}
