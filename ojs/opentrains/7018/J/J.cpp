#include <bits/stdc++.h>
#define double long double
// input
// 1: n
// n lines: xi, hi, bi

using namespace std;

const int N = 70007;
typedef double num;
typedef long long int ll;

struct point {
    double x, y;

    bool operator < (const point & ot) const
    { return ((x == ot.x && y < ot.y) || (x < ot.x)); }
    bool operator == (const point & ot) const
    { return ((x == ot.x) && (y == ot.y)); }

    double dist (point & ot)
    { return sqrt((x-ot.x)*(x-ot.x) + (y-ot.y)*(y-ot.y)); }
};

struct seg {
    point a, b;

    inline bool contains (double x)
    { return (x >= a.x && x <= b.x); }

    inline double getAlpha ()
    { return (a.y-b.y)/(a.x-b.x); }

    inline double getBeta (double alpha)
    { return (a.y - alpha*a.x); }

    double cross (seg & t) {
        double as = getAlpha();
        double at = t.getAlpha();

        double x = (getBeta(as) - t.getBeta(at))/(at - as);
        if (contains(x) && t.contains(x))
            return x;
        return 1./0.;
    }

    double getY (double x) {
        if (!contains(x))
            return 0.;

        double al = getAlpha();
        return al*x + getBeta(al);
    }
};

int n, m;
point pts[3*N];
point inte[3*N];
int x, h, b;
seg s, t;

int main () {
    int ts = 0;
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &x, &h, &b);
            
            pts[3*i].x = -.5*b + x;
            pts[3*i].y = 0;
            inte[3*i] = pts[3*i];

            pts[3*i+1].x = x;
            pts[3*i+1].y = h;
            inte[3*i+1] = pts[3*i+1];

            pts[3*i+2].x = .5*b + x;
            pts[3*i+2].y = 0;
            inte[3*i+2] = pts[3*i+2];
        }

        m = 3*n;
        for (int i = 0; i < 3*n; i++) {
            if (i%3 == 2) continue;
            s.a = pts[i];
            s.b = pts[i+1];

            for (int j = i+1; j < 3*n; j++) {
                if (j%3 == 2) continue;
                t.a = pts[j];
                t.b = pts[j+1];

                inte[m].x = s.cross(t);
                inte[m].y = 0.;
                m += (inte[m].x != 1./0.);
            }
        }

        sort(inte, inte+m);
        m = unique(inte, inte+m) - inte;

        double res = 0.;
        for (int i = 0; i < m; i++) {
            inte[i].y = 0.;

            for (int j = 0; j < 3*n; j++) {
                if (j%3 == 2)
                    continue;

                s.a = pts[j];
                s.b = pts[j+1];

                inte[i].y = max(inte[i].y, s.getY(inte[i].x));
            }
            
            if (i && inte[i-1].y + inte[i].y != 0.) {
                res += inte[i-1].dist(inte[i]);
         //       printf("(%.2f,%.2f) -> (%.2f,%.2f) + %.2f\n", inte[i-1].x, inte[i-1].y, inte[i].x, inte[i].y, inte[i-1].dist(inte[i]));
            }
        }
        printf("Case %d: ", ++ts);
        printf("%.0Lf\n\n", floor(res+0.5));
    }
}
