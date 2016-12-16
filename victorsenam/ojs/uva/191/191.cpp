#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;

// ## about eps ##
// many functions recieve an optional parameter eps
// when dealing with floating point numbers, eps is the size of a point
// if you want points to be considered as existant, eps should be positive
// otherwise, eps should be negative

template<typename cood=ll> struct vect {
    cood x,y;
    
    // constructors
    vect<cood> () {}
    vect<cood> (cood a, cood b) : x(a), y(b) {}
    vect<cood> (cood a) : x(a), y(a) {}

    // basics
    inline bool operator < (const vect<cood> & ot) const // lex compare
    { return (x < ot.x || (x == ot.x && y < ot.y)); }

    // transforming
    inline vect<cood> operator - (const vect<cood> & ot) const
    { return vect<cood>(x - ot.x, y-ot.y); }
    inline vect<cood> operator + (const vect<cood> & ot) const
    { return vect<cood>(x + ot.x, y + ot.y); }
    inline vect<cood> flip () const
    { return vect<cood>(y, x); }
    inline vect<cood> mirror () const
    { return vect<cood>(-y, x); }

    // math
    inline cood operator * (const vect<cood> & ot) const // cross
    { return x * ot.y - y * ot.x; }
    inline cood operator ^ (const vect<cood> & ot) const // inner
    { return x * ot.x + y * ot.y; }
    inline cood sq (const vect<cood> & ot = 0) const // squared 2-norm (and distance)
    { return (*this)^(*this); }
    inline cood norm (const vect<cood> & ot = 0) const // 2-norm (and distance)
    { return sqrt(sq(ot)); }
    inline cood area (const vect<cood> & a, const vect<cood> & b) const // oriented area (positive if b is to the right of a)
    { return (a-(*this))*(b-(*this)); }
    inline int clockwise (const vect<cood> & a, const vect<cood> & b, cood eps = 0) const // clockwise comparsion (to the right means greater)
    { cood o = area(a, b); return (o > eps) - (o < -eps); }

    int inside (const vector<vect<cood> > & poly, cood eps = 0) const {
        int n = poly.size();
        int anc = poly[n-1].clockwise(*this, poly[0], eps);
        if (!anc) return 0;

        for (int i = 0; i < n-1; i++) {
            int loc = poly[i].clockwise(*this, poly[i+1], eps);
            if (loc != anc) return 0;
        }

        return 1;
    }
};

template<typename cood=ll>
struct interval {
    cood a,b;

    interval<cood> () {}
    interval<cood> (cood s, cood t) : a(s), b(t)
    { if (a > b) swap(a,b); }
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
    line<cood> (vect<cood> a, vect<cood> b) : s(a), t(b)
    {  if (t < s) swap(s,t); }

    inline line<cood> flip () const
    { return line<cood>(s.flip(), t.flip()); }
    inline vect<cood> dir () const
    { return t-s; }

    inline cood sq_dist (const vect<cood> & ot) const // squared distance to a vector
    { return min(s.sq(ot), t.sq(ot)); }

    // XXX: this breaks if s = t
    bool intersects (const line<cood> & ot, cood eps = 0) const {
        int a = s.clockwise(t, ot.s, eps); int b = s.clockwise(t, ot.t, eps);

        if (a == 0 && b == 0) { // colinear corner
            if (line<cood>(s, (s + dir().mirror())).intersects(ot)) return 1;
            if (line<cood>(t, (t + dir().mirror())).intersects(ot)) return 1;
            return 0;
        }

        if (a == b) return 0;
        if (ot.s.clockwise(ot.t, s, eps) == ot.s.clockwise(ot.t, t, eps)) return 0;
        return 1;
    }
};

int n;
vect<ll> v[4];
line<ll> l;

int main () {
    scanf("%d", &n);

    while (n--) {
        scanf("%d %d %d %d", &l.s.x, &l.s.y, &l.t.x, &l.t.y);
        scanf("%d %d", &v[0].x, &v[0].y);
        scanf("%d %d", &v[2].x, &v[2].y);

        v[1].x = v[0].x; v[1].y = v[2].y;
        v[3].x = v[2].x; v[3].y = v[0].y;

        bool ok = 0;
        if (l.s.inside({v[0], v[1], v[2], v[3]}) || l.t.inside({v[0], v[1], v[2], v[3]}))
            ok = 1;
        else {
            for (int j = 0; j < 4; j++)
                ok |= l.intersects(line<ll>(v[j], v[(j+1)%4]));
        }
        
        if (ok) printf("T\n");
        else printf("F\n");
    }
}
