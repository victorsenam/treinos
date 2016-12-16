#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;
//typedef ll cood;

const db eps = 1e-8;

template<typename cood=ll> struct vect {
    cood x,y;
    
    vect<cood> () {}
    vect<cood> (cood a, cood b) : x(a), y(b) {}

    inline vect<cood> operator - (const vect<cood> & ot) const
    { return vect<cood>(x - ot.x, y-ot.y); }
    inline vect<cood> operator + (const vect<cood> & ot) const
    { return vect<cood>(x + ot.x, y + ot.y); }

    inline cood operator * (const vect<cood> & ot) const // cross
    { return y * ot.x - x * ot.y; }
    inline cood operator ^ (const vect<cood> & ot) const // inner
    { return x * ot.x + y * ot.y; }

    inline cood sq () const
    { return (*this)^(*this); }
    inline cood norm () const
    { return sqrt(sq()); }

    inline cood orient (const vect<cood> & a, const vect<cood> & b) const
    { return (a-(*this))*(b-(*this)); }
    
    // position of vector relative to convex polygon
    // poly : convex polygon given by sequence of vectors ordered by angle
    //        (clockwise or counter-clockwise)
    // return 1 if strictly inside and 0 if not
    bool inside (const vector<vect<cood> > & poly) const {
        int n = poly.size();
        cood anc = poly[n-1].orient(*this, poly[0]);
        if (anc > 0) anc = 1;
        else if (anc < 0) anc = -1;
        else return 0;

        for (int i = 0; i < n-1; i++) {
            cood rel = anc*poly[i].orient(*this, poly[i+1]);
            if (rel <= 0) return 0;
        }

        return 1;
    }
};

template<typename cood=ll> struct line {
    vect<cood> s,t;

    line<cood> () {}
    line<cood> (vect<cood> a, vect<cood> b) : s(a), t(b) {
        if (s.x > t.x) swap(s, t);
    }
    
    inline vect<cood> dir () const
    { return t - s; }
    inline double slope () const
    { return double(dir().y) / double(dir().x); }
    inline double intercept (double a = slope()) const
    { return s.y - a * s.x; }

    // is there a point with this value of x inside the segment?
    // x : given value
    // returns a boolean
    bool contains (const double x) const {
        return s.x - eps < x && x < t.x + eps;
    }

    // gets the intersection between two lines (not segments)
    // ot : the other line
    // if they are equal, returns nan
    // if they are parallel, returns inf
    // else, returns the x on which the intersection occurs
    double intersection (const line<cood> & ot) const {
        double a[2] = {slope(), ot.slope()};
        double b[2] = {intercept(a[0]), ot.intercept(a[1])};

        if (abs(a[0]-a[1]) < eps) {
            if (abs(b[0]-b[1]) < eps) return 0./0.;
            return 1./0.;
        } else {
            debug("%.2f/%.2f", b[0]-b[1], a[1]-a[0]);
            return (b[0]-b[1])/(a[1]-a[0]);
        }
        
        return true;
    }
};

int n;
line<> v;
vect<> a[4];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        debug("%d: ", i);
        scanf("%lld %lld", &v.s.x, &v.s.y);
        scanf("%lld %lld", &v.t.x, &v.t.y);

        scanf("%lld %lld", &a[0].x, &a[0].y);
        scanf("%lld %lld", &a[2].x, &a[2].y);

        a[1].x = a[0].x;
        a[1].y = a[2].y;

        a[3].x = a[2].x;
        a[3].y = a[0].y;

        if (v.s.inside({a[0], a[1], a[2], a[3]}) || v.t.inside({a[0], a[1], a[2], a[3]})) {
            debug("1");
            printf("T\n");
            continue;
        }

        int j = 0;
        for (j = 0; j < 4; j++) {
            line<> u(a[j], a[(j+1)%4]);

            double x = v.intersection(u);
            if (x == 0./0.) {
                debug("e");
                if (v.contains(u.s.x) || v.contains(u.t.x) || u.contains(v.s.x) || u.contains(v.t.x))
                    break;
            } else if (v.contains(x) && u.contains(x)) {
                debug("c");
                break;
            } else {
                debug("[%.1f]", x);
            }
        }

        if (j == 4) 
            printf("F\n");
        else
            printf("T\n");
    }
}
