#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;
//typedef ll cood;

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
    inline cood orient (const vect<cood> & a, const vect<cood> & b) const // oriented area
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

template<typename cood=ll>
struct interval {
    cood a,b;

    interval<cood> () {}
    interval<cood> (cood s, cood t) : a(s), b(t) {
        if (a > b) swap(a,b);
    }
    interval<cood> (cood x) : a(x), b(x) {}

    inline bool intersects (const interval & ot) {
        if (a < ot.a) return b > ot.a;
        if (b > ot.b) return a < ot.b;
        return 1;        
    }

    inline bool contains (const interval & ot)
    { return a <= ot.a && b >= ot.b; }
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

    double slope () const {
        if (s.x == t.x) return double(s.y != t.y)/0.;
        return double(t.y - s.y)/double(t.x - s.x);
    }
    double intersept (double a) const
    { return s.y - a*s.x; }
    double intersept () const
    { return intersept(slope()); }
    
    double get (double x) {
        if (s.x == t.x)
            return 0./0.;
        return x*slope() + intersept();
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

        scanf("%lld %lld", &a[0].x, &a[0].y);
        scanf("%lld %lld", &a[2].x, &a[2].y);

        a[1].x = a[0].x;
        a[1].y = a[2].y;

        a[3].x = a[2].x;
        a[3].y = a[0].y;

        bool ok = 0;
        if (v.s.inside({a[0], a[1], a[2], a[3]}) || v.t.inside({a[0], a[1], a[2], a[3]})) {
            ok = 1;
        } else if (v.s.x == v.t.x) {
            if (interval<ll>(a[0].x, a[2].x).contains(v.s.x) &&
                interval<ll>(a[0].y, a[2].y).intersects(interval<ll>(v.s.y, v.t.y)) )
                    ok = 1;
        } else if (v.s.y == v.t.y) {
            if (interval<ll>(a[0].y, a[2].y).contains(v.s.y) &&
                interval<ll>(a[0].x, a[2].x).intersects(interval<ll>(v.s.x, v.t.x)) )
                    ok = 1;
        } else {
            if (interval<double>(a[0].x-eps, a[2].x+eps).contains(v.flip().get(a[0].y))) ok = 1;
            if (interval<double>(a[0].x-eps, a[2].x+eps).contains(v.flip().get(a[2].y))) ok = 1;

            if (interval<double>(a[0].y-eps, a[2].y+eps).contains(v.get(a[0].x))) ok = 1;
            if (interval<double>(a[0].y-eps, a[2].y+eps).contains(v.get(a[2].x))) ok = 1;
        }

        if (!ok)
            printf("F\n");
        else
            printf("T\n");
    }
}
