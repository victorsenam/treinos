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

// ## complexity ##
// last line in comments means complexity
// time | space

template<typename cood=ll> struct vect;
template<typename cood=ll> struct interval;
template<typename cood=ll> struct line;
template<typename cood=ll> struct poly;

template<typename cood> struct vect {
    cood x,y;
    
    // constructors
    vect<cood> () {}
    vect<cood> (cood a, cood b) : x(a), y(b) {}
    vect<cood> (cood a) : x(a), y(a) {}

    // basics
    inline bool operator < (const vect<cood> & ot) const // lex compare
    { return (x < ot.x || (x == ot.x && y < ot.y)); }
    inline void print () const
    { printf("(%lld,%lld)", x, y); }

    // transforming
    inline vect<cood> operator - (const vect<cood> & ot) const
    { return vect<cood>(x - ot.x, y - ot.y); }
    inline vect<cood> operator + (const vect<cood> & ot) const
    { return vect<cood>(x + ot.x, y + ot.y); }
    inline vect<cood> flip () const
    { return vect<cood>(y, x); }
    inline vect<cood> mirror () const
    { return vect<cood>(-y, x); }

    // math
    inline cood operator * (const vect<cood> & ot) const // cross
    { return y * ot.x - x * ot.y; }
    inline cood operator ^ (const vect<cood> & ot) const // inner
    { return x * ot.x + y * ot.y; }
    inline cood sq (const vect<cood> & ot = 0) const // squared 2-norm (and distance)
    { return (*this)^(*this); }
    inline cood norm (const vect<cood> & ot = 0) const // 2-norm (and distance)
    { return sqrt(sq(ot)); }
    inline cood area (const vect<cood> & a, const vect<cood> & b) const // oriented area (positive if b is to the right of a)
    { return (a-(*this))*(b-(*this)); }
    int clockwise (const vect<cood> & a, const vect<cood> & b, cood eps = 0) const // clockwise comparsion (to the right means greater)
    { cood o = area(a, b); return (o > eps) - (o < -eps); }

    // XXX doesn't work with non-convex, doesn't check for convexity
    // position of vector relative to convex polygon
    // poly : the vertices of the polygon (ordered in any way)
    // returns 1 if strictly inside
    // returns 0 if on the border
    // returns -1 if outside
    // O(n) | O(1)
    int position (const poly<cood> & pl, cood eps = 0) const {
        int n = pl.v.size();
        int lo = 0; int hi = n-1;

        while (lo < hi) {
            int mid = lo+(hi-lo+1)/2; 
            
            if (pl.v[0].clockwise(pl.v[mid], *this, eps) >= 0)
                lo = mid;
            else
                hi = mid-1;
        }

        if (lo == n-1 && pl.v[n-2].clockwise(pl.v[n-1], *this, eps) == -1) return -1;
        return pl.v[lo].clockwise(pl.v[(lo+1)%n], *this, eps);
    }
};

template<typename cood> struct interval {
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

template<typename cood> struct line {
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

    bool intersects (const line<cood> & ot, cood eps = 0) const {
        int a = s.clockwise(t, ot.s, eps); int b = s.clockwise(t, ot.t, eps);

        if (a == 0 && b == 0) { // colinear corner
            if (!interval<cood>(s.x, t.x).intersects(interval<cood>(ot.s.x, ot.t.x), eps)) return 0;
            if (!interval<cood>(s.y, t.y).intersects(interval<cood>(ot.s.y, ot.t.y), eps)) return 0;
            return 1;
        }

        if (a == b) return 0;
        if (ot.s.clockwise(ot.t, s, eps) == ot.s.clockwise(ot.t, t, eps)) return 0;
        return 1;
    }
};

template<typename cood> struct poly {
    vector<vect<cood> > v;

    poly<cood> () {}
    poly<cood> (const vector<vect<cood> > & inp) : v(inp) {}

    // applies Graham's algorithm for convex hull
    // returns convex hull of polygon
    // O(n lg(n)) | O(n)
    poly<cood> graham (cood eps = 0) const {
        int mini = 0;
        vector<int> p;
        for (int i = 0; i < v.size(); i++) {
            p.push_back(i);
            if (v[i] < v[mini]) 
                mini = i;
        }
        swap(p[0], p[mini]);

        int anc = p[0];
        sort(p.begin() + 1, p.end(), [anc, this](int i, int j) -> bool { (v[anc].clockwise(v[i], v[j], 0) == 1); });

        vector<vect<cood> > r;
        for (int _i : p) {
            vect<cood> c = v[p[_i]];
            while (r.size() > 1 && !r[r.size()-2].clockwise(r[r.size()-1], c, eps) != 1)
                r.pop();
            r.push_back(c);
        }
        
        return r;
    }
};

int n;
vect<ll> v[4];
line<ll> l;

int main () {
    scanf("%d", &n);

    while (n--) {
        scanf("%lld %lld %lld %lld", &l.s.x, &l.s.y, &l.t.x, &l.t.y);
        scanf("%lld %lld", &v[0].x, &v[0].y);
        scanf("%lld %lld", &v[2].x, &v[2].y);

        if (v[0].x > v[2].x) swap(v[0].x, v[2].x);
        if (v[0].y < v[2].y) swap(v[0].y, v[2].y);

        v[1].x = v[2].x; v[1].y = v[0].y;
        v[3].x = v[0].x; v[3].y = v[2].y;

        assert(v[0].clockwise(v[1], v[2]));

        bool ok = 0;
        if (l.s.position(poly<ll>({v[0], v[1], v[2], v[3]})) >= 0 || l.t.position(poly<ll>({v[0], v[1], v[2], v[3]})) >= 0)
            ok = 1;
        else {
            for (int j = 0; j < 4; j++)
                ok |= l.intersects(line<ll>(v[j], v[(j+1)%4]));
        }
        
        if (ok) printf("T\n");
        else printf("F\n");
    }
}
