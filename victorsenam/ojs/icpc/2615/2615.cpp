#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef complex<ll> pt;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 300;
const int B = 60;

pt pts[N];
pt ref;
int n, b;
int x, y;
pt cvx[N];
int sc;
ll memo[N][N][B];
int visi[N][N][B], turn;

inline ll cross (pt a, pt b)
{ return (conj(ref)*a).imag(); }

bool cmp_c (pt a, pt b) {
    a -= pts[0]; b -= pts[0];
    if ((cross(ref, a))^(cross(ref, b)) < 0)
        return cross(ref, a) < cross(ref, b);
    return cross(a, b) < 0;
}

ll pd (int s, int t, int b) {
    if (t-s <= 1) return LLONG_MAX-10;

    ll & me = memo[s][t][b];
    if (visi[s][t][b] == turn)
        return me;
    visi[s][t][b] = turn;
    me = LLONG_MAX-10;

    if (b == 1) {
        sc = 0;
        for (int i = s; i < t; i++) {
            while (sc >= 2 && cross(cvx[sc-1] - cvx[sc-2], pts[i] - cvx[sc-2]) >= 0) sc--;
            cvx[sc++] = pts[i];
        }
        me = 0.;
        DEBUG("[%d,%d):", s, t);
        for (int i = 0; i < sc; i++) {
            me += abs(cross(cvx[i]-pts[0], cvx[i]-pts[1]));
            DEBUG(" (%lld,%lld)", cvx[i].real(), cvx[i].imag());
        }
        DEBUG("\n");
        return me;
    }

    for (int i = s+1; i < t; i++) {
        ll loc = pd(s, i, 1) + pd(s, i, b-1);
        if (loc < 0) loc = LLONG_MAX;
        me = min(me, loc);
    }
    return me;
}

int main () {
    while (scanf("%d %d", &b, &n) != EOF && n) {
        ++turn;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            pts[i] = pt(x, y);
        }
        ref = pts[1] - pts[0];

        sort(pts+2, pts+n, cmp_c);
        for (int i = 1; i < n; i++) {
            pts[i+n-1] = pts[i];
            DEBUG("%d : (%lld,%lld)\n", i, pts[i].real(), pts[i].imag());
        }

        ll res = LLONG_MAX;

        for (int i = 1; i < n; i++)
            res = min(res, pd(i, i+n-1, b));
        printf("%lld", res/2);
        if (res&1)
            printf(".50\n");
        else
            printf(".00\n");
    }
}
