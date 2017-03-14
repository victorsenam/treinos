#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef double db;

//#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#define DEBUG(...) {}

const int N = 1007;
<<<<<<< HEAD

struct point {
    db x, y;

    point () {}
    point (db a, db b) : x(a), y(b) {}
};

int n;
db cd[N][3];
db memo[N][2];
db lo, hi;

inline db sq (db x)
{ return x*x; }
inline db dist (point a, point b)
{ return sqrt(sq(a.x-b.x)+sq(a.y-b.y)); }
inline db expand (point a, point b, point c) {
    db y = a.y - b.y;
    db h = a.y - c.y;
    db x = a.x - b.x;

    db r = a.x - h*x/y;

    return r;
}

void intersect (db & lo, db & hi, db l, db r) {
    if (l <= lo && hi <= r)
        return;
    if (lo <= l && r <= hi) {
        lo = l;
        hi = r;
        return;
    }
    if (lo >= r || hi <= l) {
        lo = 1./0.;
        hi = -lo;
        return;
    }

    lo = max(lo, l);
    hi = min(hi, r);
=======
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
>>>>>>> 67a8388d472f2e55cffe7cde6c42bcebc5bd600f
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        scanf("%lf %lf", &cd[0][1], &cd[0][0]);

        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 3; j++)
                scanf("%lf", &cd[i][j]);

        for (int i = n-1; i >= 0; i--) {
            for (int s = 0; s < 2; s++) {
<<<<<<< HEAD
                int j;
                db & me = memo[i][s];
                point curr(cd[i][1+s], cd[i][0]);

                me = 1./0.;

                lo = cd[i+1][1];
                hi = cd[i+1][2];

                for (j = i+1; j <= n && lo <= cd[j][2] && cd[j][1] <= hi; j++) {
                    if (lo <= cd[j][1]) {
                        me = min(me, memo[j][0] + dist(curr, {cd[j][1], cd[j][0]}));
                        DEBUG("(%d,%d) -> (%d,%d) : %.4f + %.4f", i, s, j, 0, memo[j][0], dist(curr, {cd[j][1], cd[j][0]}));
                        DEBUG(" = %.4f\n", memo[j][0] + dist(curr, {cd[j][1], cd[j][0]}));
                    }
                    if (hi >= cd[j][2]) {
                        me = min(me, memo[j][1] + dist(curr, {cd[j][2], cd[j][0]}));
                        DEBUG("(%d,%d) -> (%d,%d) : %.4f + %.4f", i, s, j, 1, memo[j][1], dist(curr, {cd[j][2], cd[j][0]}));
                        DEBUG(" = %.4f\n", memo[j][1] + dist(curr, {cd[j][2], cd[j][0]}));
                    }

                    if (j < n) {
                        DEBUG("%d~%d -> %d~%d from [%.4f,%.4f] and ", i, j, i, j+1, lo, hi);
                        lo = expand(curr, {lo, cd[j][0]}, {cd[j+1][1], cd[j+1][0]});
                        hi = expand(curr, {hi, cd[j][0]}, {cd[j+1][2], cd[j+1][0]});
                        DEBUG("[%.4f,%.4f] to ", lo, hi);
                        intersect(lo, hi, cd[j+1][1], cd[j+1][2]);
                        DEBUG("[%.4f,%.4f]\n", lo, hi);
                    }
                }

                if (j == n+1) {
                    if (lo <= curr.x && curr.x <= hi) {
                        me = min(me, dist(curr, {curr.x, cd[n][0]}));
                    }
                    me = min(me, dist(curr, {lo, cd[n][0]}));
                    me = min(me, dist(curr, {hi, cd[n][0]}));
                }

                //DEBUG("(%d,%d) : %.4f\n", i, s, me);
=======
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
>>>>>>> 67a8388d472f2e55cffe7cde6c42bcebc5bd600f
            }
        }

        printf("%.20f\n", memo[0][0]);
    }
}
