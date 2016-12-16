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

    // position of vector relative to convex polygon
    // poly : convex polygon given by sequence of vectors ordered by angle
    //        (clockwise or counter-clockwise)
    // return -1 if strictly outside
    // return 0 if on the border
    // return 1 if strictly inside
    int position (const vector<vect<cood> > & poly, cood eps = 0) const {
        int n = poly.size();
        int anc = poly[n-1].clockwise(*this, poly[0], eps);
        if (anc == 0) return 0;

        for (int i = 0; i < n-1; i++) {
            int loc = poly[i].clockwise(*this, poly[i+1], eps);
            if (loc == 0) return 0;
            if (loc != anc) return -1;
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

    inline line<cood> flip ()
    { return line<cood>(s.flip(), t.flip()); }

    inline cood sq_dist (const line<cood> & ot) const // squared distance to another segment
    { return min{s.sq(ot.s), s.sq(ot.t), t.sq(ot.s), t.sq(ot.t)}; }

    bool intersects (const line<cood> & ot, cood eps = 0) const {
        int a = s.clockwise(t, ot.s, eps); int b = s.clockwise(t, ot.t, eps);

        if (a == 0 && b == 0) // colinear corner
            return (sq_dist(ot) < s.sq(t) + eps);

        if (a == b) return 0;
        if (ot.s.clockwise(ot.t, s, eps) == ot.s.clockwise(ot.t, t, eps)) return 0;
        return 1;
    }
};

int main () {
}
