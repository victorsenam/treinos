#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef complex<ll> pt;

#define ONLINE_JUDGE
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
{ return (conj(a)*b).imag(); }

bool cmp_c (pt a, pt b) {
    DEBUG("(%lld,%lld) < (%lld,%lld): ", a.real(), a.imag(), b.real(), b.imag());
    a -= pts[0]; b -= pts[0];
    ll ca = cross(a, ref);
    ll cb = cross(b, ref);
    DEBUG("[%d]", (ca^cb) < 0);
    DEBUG(" = %d\n", ((ca^cb)<0)?ca<cb:cross(a,b)>0);
    if ((ca^cb) < 0)
        return ca < cb;
    return cross(a, b) > 0;
}

ll pd (int s, int t, int b) {
    if (t-s <= 1) return LLONG_MAX;

    ll & me = memo[s][t][b];
    if (visi[s][t][b] == turn)
        return me;
    visi[s][t][b] = turn;
    me = LLONG_MAX;

    if (b == 1) {
        sc = 0;
        for (int i = s; i < t; i++) {
            while (sc >= 2 && cross(cvx[sc-1] - cvx[sc-2], pts[i] - cvx[sc-2]) <= 0) sc--;
            cvx[sc++] = pts[i];
        }
        me = 0;
        
        DEBUG("[%d,%d):", s, t);
        if (cross(cvx[0]-pts[0], cvx[sc-1]-pts[0]) < 0) {
            me = LLONG_MAX;
            DEBUG("INVALID");
        } else {
            for (int i = 1; i < sc; i++) {
                me += abs(cross(cvx[i]-pts[0], cvx[i-1]-pts[0]));
                DEBUG(" (%lld,%lld)", cvx[i].real(), cvx[i].imag());
            }
        }
        DEBUG("-> %lld \n", me);
        return me;
    }

    for (int i = s+1; i < t-1; i++) {
        ll loc = max(max(pd(s, i, 1) + pd(i, t, b-1), pd(s, i, 1)), pd(i, t, b-1));
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
        //for (int i = 1; i < n; i++)
         //   DEBUG("(%lld,%lld) hemisferio %d\n", pts[i].real(), pts[i].imag(), cross(pts[i]-pts[0], ref) > 0);

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
