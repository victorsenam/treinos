#include <bits/stdc++.h>
//#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#define debug(...) {}

using namespace std;
typedef long long int ll;
typedef double db;

// eps is the size of a point
// if you want points to be considered as existant, eps should be positive
// otherwise, eps should be negative
const db eps = 1e-8;

template<typename cood=ll> struct vect {
    cood x,y;
    
    // constructors
    vect<cood> () {}
    vect<cood> (cood a, cood b) : x(a), y(b) {}

    // basics
    inline bool operator < (const vect<cood> & ot) const
    { return (x < ot.x || (x == ot.x && y < ot.y)); }

    // transforming
    inline vect<cood> operator - (const vect<cood> & ot) const
    { return vect<cood>(x - ot.x, y-ot.y); }
    inline vect<cood> operator + (const vect<cood> & ot) const
    { return vect<cood>(x + ot.x, y + ot.y); }
    inline vect<cood> flip () const
    { return vect<cood>(y, x); }

    // math
    inline cood operator * (const vect<cood> & ot) const // cross
    { return y * ot.x - x * ot.y; }
    inline cood operator ^ (const vect<cood> & ot) const // inner
    { return x * ot.x + y * ot.y; }
    inline cood sq () const // squared 2-norm
    { return (*this)^(*this); }
    inline cood norm () const // 2-norm
    { return sqrt(sq()); }
    inline cood area (const vect<cood> & a, const vect<cood> & b) const // oriented area
    { return (a-(*this))*(b-(*this)); }
    inline int orient (const vect<cood> & a, const vect<cood> & b, cood eps = 0) const {
        cood o = area(a, b);
        return (o > eps) - (o < -eps);
    }

    // position of vector relative to convex polygon
    // poly : convex polygon given by sequence of vectors ordered by angle
    //        (clockwise or counter-clockwise)
    // return 1 if strictly inside and 0 if not
    bool inside (const vector<vect<cood> > & poly, cood eps = 0) const {
        int n = poly.size();
        int anc = poly[n-1].orient(*this, poly[0], eps);

        for (int i = 0; i < n-1; i++) {
            int rel = anc*poly[i].orient(*this, poly[i+1], eps);
            if (rel <= 0) return 0;
        }

        return 1;
    }
};

template<typename cood=ll>
struct interval {
    cood a,b;

    interval<cood> () {}
    interval<cood> (cood s, cood t) : a(s), b(t) {
        if (a > b) swap(a,b);
    }
    interval<cood> (cood x) : a(x), b(x) {}

    inline bool contains (const interval & ot, cood eps = 0) const
    { return a - eps <= ot.a && ot.b <= b + eps; }

    inline bool intersects (const interval & ot, cood eps = 0) const
    { return contains(ot.a, eps) || contains(ot.b, eps) || ot.contains(*this, eps); }
};

template<typename cood=ll>
struct line {
    vect<cood> s, t;
    
    line<cood> () {}
    line<cood> (vect<cood> a, vect<cood> b) : s(a), t(b) {
        if (t < s) swap(s,t);
    }

    inline line<cood> flip ()
    { return line<cood>(s.flip(), t.flip()); }

    bool intersects (const line<cood> & ot, cood eps = 0) const {
        if (s.orient(t, ot.s, eps)*s.orient(t, ot.t, eps) > 0) return 0;
        if (ot.s.orient(ot.t, s, eps)*ot.s.orient(ot.t, t, eps) > 0) return 0;
        return 1;
    }

    double slope (cood eps = 0) const {
        if (abs(s.x - t.x) < eps) {
            assert(false);
            return double(abs(s.y - t.y) > eps)/0.;
        }
        return double(t.y - s.y)/double(t.x - s.x);
    }
    double get (double x, cood eps = 0) const {
        if (abs(s.x - t.x) < eps) {
            assert(false);
            return 0./0.;
        }
        double a = slope(eps);
        return (x - double(s.x))*a + double(s.y);
    }

    
};

int n;
line<> v;
vect<> a[4];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &v.s.x, &v.s.y);
        scanf("%lld %lld", &v.t.x, &v.t.y);
        v = line<ll>(v.s, v.t);

        scanf("%lld %lld", &a[0].x, &a[0].y);
        scanf("%lld %lld", &a[2].x, &a[2].y);
        if (a[0].x > a[2].x) swap(a[0].x, a[2].x);
        if (a[0].y > a[2].y) swap(a[0].y, a[2].y);

        a[1].x = a[0].x;
        a[1].y = a[2].y;

        a[3].x = a[2].x;
        a[3].y = a[0].y;

        bool ok = 0;
        if (v.s.inside({a[0], a[1], a[2], a[3]}) || v.t.inside({a[0], a[1], a[2], a[3]})) {
            ok = 1;
        } else if (v.s.x == v.t.x) {
            debug("v");
            if (interval<ll>(a[0].x, a[2].x).contains(v.s.x) &&
                interval<ll>(a[0].y, a[2].y).intersects(interval<ll>(v.s.y, v.t.y)) )
                    ok = 1;
        } else if (v.s.y == v.t.y) {
            debug("h");
            if (interval<ll>(a[0].y, a[2].y).contains(v.s.y) &&
                interval<ll>(a[0].x, a[2].x).intersects(interval<ll>(v.s.x, v.t.x)) )
                    ok = 1;
        } else {
            for (int j = 0; j < 4; j++)
                if (v.intersects(line<ll>(a[j], a[(j+1)%4]))) 
                    ok = 1;
        }

        if (!ok)
            printf("F\n");
        else
            printf("T\n");
    }
}
