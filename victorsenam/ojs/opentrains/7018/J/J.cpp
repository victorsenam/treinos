#include <bits/stdc++.h>

using namespace std;

const int N = 70007;
typedef double ll;

ll pts[N][2];
int n;
double inter[N];
int ints;

ll cross (int anc, int i, int j) {
    ll a[2], b[2];
    for (int k = 0; k < 2; k++) {
        a[k] = pts[i][k]-pts[anc][k];
        b[k] = pts[j][k]-pts[anc][k];
    }

    return a[0]*b[1] - a[1]*b[0];
}

double getA (int i, int j)
{ return double(pts[i][1] - pts[j][1])/double(pts[i][0] - pts[j][0]); }
double getB (int i, double a)
{ return double(pts[i][1]) - a*double(pts[i][0]); }
double getY (int i, double x) {
    if (x < pts[i][0] || x > pts[i+1][0])
        return 0.;
    double a = getA(i, i+1);
    return a*x + getB(i, a);
}

double getIntersection (int i, int j) {
    ll c1 = cross(i, i+1, j);
    ll c2 = cross(i, i+1, j+1);

    if ((c1 < 0 && c2 < 0) || (c1 > 0 && c2 > 0) || (c1 == 0 && c2 == 0))
        return 1./0.;

    double a[2], b[2];
    a[0] = getA(i, i+1); a[1] = getA(j, j+1);
    b[0] = getB(i, a[0]); b[1] = getB(j, a[1]);

    return (b[1]-b[0])/(a[0]-a[1]);
}

inline double sq (double val)
{ return val*val; }
inline double dist (int i, int j)
{ return sqrt(sq(pts[i][0]-pts[j][0])+sq(pts[i][1]-pts[j][1])); }

int main () {
    int ts = 0;
    while (scanf("%d", &n) && n) {
        ints = 0;
        for (int i = 0; i < n; i++) {
            ll h, b, x;

            scanf("%lf %lf %lf", &x, &h, &b);
            pts[(i<<2)][0] = x-.5*b; pts[(i<<2)][1] = 0.;
            pts[(i<<2)+1][0] = x; pts[(i<<2)][1] = h;
            pts[(i<<2)+2][0] = x; pts[(i<<2)][1] = h;
            pts[(i<<2)+3][0] = x+.5*b; pts[(i<<3)+3][1] = 0.;

            inter[ints++] = x-.5*b; inter[ints++] = x; inter[ints++] = x+.5*b;
        }
        pts[(n<<2)][0] = -1./0.; pts[(n<<2)][1] = 0.;

        for (int i = 0; i < (n<<2); i += 2) {
            for (int j = i+2; j < (n<<2); j+= 2) {
                double val = getIntersection(i, j);
                if (val != 1./0.)
                    inter[ints++] = val;
            }
        }

        sort(inter, inter+ints);
        ints = unique(inter, inter+ints) - inter;

        double res = 0.;
        for (int i = 0; i < ints; i++) {
            pts[(n<<2)+1][0] = inter[ints];
            pts[(n<<2)+1][1] = 0.;
            for (int i = 0; i < (n<<2); i += 2)
                pts[(n<<2)+1][1] = max(pts[(n<<2)+1][1], getY(i, inter[ints]));

            if (pts[(n<<2)][1] != 0. || pts[(n<<2)+1][1] != 0.)
                res += dist((n<<2), (n<<2)+1);

            pts[(n<<2)][0] = pts[(n<<2)+1][0];
            pts[(n<<2)][1] = pts[(n<<2)+1][1];
        }

        printf("Case %d: %.0f\n\n", ++ts, res+.5);
    }
}
