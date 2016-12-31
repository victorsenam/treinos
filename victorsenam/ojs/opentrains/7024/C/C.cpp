#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#define fst first
#define snd second

using namespace std;
typedef long long int ll;
typedef double db;

const double eps = 1e-3;

// ## about eps ##
// many functions recieve an optional parameter eps
// when dealing with floating point numbers, eps is the size of a point
// if you want points to be considered as existant, eps should be positive
// otherwise, eps should be negative

// ## complexity ##
// last line in comments means complexity
// time | space
// standart: O(1) | O(1)

template<typename cood=ll> struct interval;
template<typename cood=ll> struct vect;
template<typename cood=ll> struct line;
template<typename cood=ll> struct poly;

template<typename cood> struct interval {
    cood a,b;

    interval<cood> () {}
    interval<cood> (cood s, cood t) : a(s), b(t)
    { if (a > b) swap(a,b); }
    interval<cood> (cood x) : a(x), b(x) {}

    // XXX assumes a <= b
    inline bool contains (const interval & ot, cood eps = 0) const
    { return a - ot.a <= eps && ot.b - b <= eps; }
    // XXX assumes a <= b
    inline bool intersects (const interval & ot, cood eps = 0) const
    { return contains(ot.a, eps) || contains(ot.b, eps) || ot.contains(*this, eps); }
};

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
    { printf("(%f,%f)", x, y); }

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
    { return ((*this)-ot)^((*this)-ot); }
    inline double norm (const vect<cood> & ot = 0) const // 2-norm (and distance)
    { return sqrt(sq(ot)); }
    inline cood area (const vect<cood> & a, const vect<cood> & b) const // oriented area (positive if b is to the right of a)
    { return (a-(*this))*(b-(*this)); }
    int clockwise (const vect<cood> & a, const vect<cood> & b, cood eps = 0) const // clockwise comparsion (to the right means greater)
    { cood o = area(a, b); return (o > -eps) - (o < eps); }
};

template<typename cood> struct line {
    vect<cood> s, t;
    
    line<cood> () {}
    line<cood> (vect<cood> a, vect<cood> b) : s(a), t(b)
    {  if (t < s) swap(s,t); }
    line<cood> (vect<cood> a) : s(a), t(a) {}

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

    // oriented area
    // O(n)
    cood area () {
        cood res = 0;
        for (int i = 1; i + 1 < v.size(); i++)
            res += v[0].area(v[i], v[i+1]);
        return res;
    }

    // applies Graham's algorithm for convex hull
    // returns convex hull of polygon
    // O(n lg(n)) | O(n)
    void graham (cood eps = 0) {
        int mini = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] < v[mini]) 
                mini = i;
        }
        swap(v[0], v[mini]);

        vect<cood> anc = v[0];
        sort(v.begin() + 1, v.end(), [anc, eps](vect<cood> i, vect<cood> j) -> bool { 
            int o = anc.clockwise(i, j, eps);
            if (!o)
                return i < j;
            return (o == 1);
        });
        v.push_back(v[0]);
        
        int m = 0;
        for (int i = 0; i < v.size(); i++) {
            while (m >= 2 + (i == v.size() - 1) && v[m-2].clockwise(v[m-1], v[i], eps) < 1)
                m--;
            swap(v[m], v[i]);
            m++;
        }
        m--;
        while (v.size() > m)
            v.pop_back();
    }

    // XXX assumes convexity
    // position of vector relative to convex polygon
    // ot : the vector
    // returns 1 if strictly inside
    // returns 0 if on the border
    // returns -1 if outside
    // O(lg(n)) | O(1)
    int position (const vect<cood> & ot, cood eps = 0) const {
        int n = v.size();
        if (n == 1) 
            return - 1 + (ot.norm(v[0]) <= eps);

        int lo = 0; int hi = n-1;
        while (lo < hi) {
            int mid = lo+(hi-lo+1)/2; 

            if (v[0].clockwise(v[mid], ot, eps) >= 0)
                lo = mid;
            else
                hi = mid-1;
        }
        
        if (lo == 0 || lo == n-1)
            return -1 + line<cood>(v[lo], v[(lo+1)%n]).intersects(line<cood>(ot,ot), eps);
        return v[lo].clockwise(v[(lo+1)%n], ot, eps);
    }

    // XXX assumes convexity
    // O(n*m + n log(m) + m log(n)) | O(1)
    bool intersects (const poly<cood> & ot, cood eps = 0) const {
        for (int i = 0; i < v.size(); i++)
            if (ot.position(v[i]) >= 0)
                return 1;
        for (int i = 0; i < ot.v.size(); i++)
            if (position(ot.v[i]) >= 0)
                return 1;

        for (int i = 0; i < v.size(); i++)
            for (int j = 0; j < ot.v.size(); j++)
                if (line<cood>(v[i], v[(i+1)%v.size()]).intersects(line<cood>(ot.v[j], ot.v[(j+1)%ot.v.size()]), eps))
                    return 1;

        return 0;
    }
};

const int N = 1e2+7;

int n;
poly<ll> pl;
vect<ll> aux;
interval<ll> base;

pair<ll, ll> cent () {
    ll cx = 0;
    ll dx = 0;
    for (int i = 1; i < pl.v.size()-1; i++) {
        ll loc = pl.v[0].area(pl.v[i], pl.v[i+1]);
        ll cen = (pl.v[0].x + pl.v[i].x + pl.v[i+1].x);

        cx += loc*cen;
        dx += loc*3ll;
    }

    return pair<ll,ll>(cx, dx);
}

int cmp (ll p, ll q, ll x) {
    if (q < 0) return cmp(-p, -q, x);
    return (p > q * x) - (p < q * x);
}

int main () {
    scanf("%d", &n);

    base.a = 2e3;
    base.b = -2e3;

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &aux.x, &aux.y);
        pl.v.push_back(aux);
 
        if (aux.y == 0.) {
            base.a = min(base.a, aux.x);
            base.b = max(base.b, aux.x);
        }
    }

    pair<ll, ll> ct = cent();
    if (ct.snd < 0) {
        ct.fst = -ct.fst;
        ct.snd = -ct.snd;
    }

    if (cmp(ct.fst, ct.snd, pl.v[0].x) > 0) {
        base.a = -base.a;
        base.b = -base.b;
        swap(base.a, base.b);
        ct.fst = -ct.fst;
        pl.v[0].x = -pl.v[0].x;
    }

    if (cmp(ct.fst, ct.snd, pl.v[0].x) == 0) {
        if (pl.v[0].x < base.a || pl.v[0].x > base.b) {
            printf("unstable\n");
        } else {
            printf("0 .. inf\n");
        }
    } else if ((pl.v[0].x <= base.a) || (cmp(ct.fst, ct.snd, base.b) > 0)) {
        printf("unstable\n");
    } else {
        ll lim[2];

        ll lo = 0;
        ll hi = 2e11;

        while (lo < hi) {
            ll mid = lo + (hi-lo)/2;

            if (cmp(ct.fst + 6ll * pl.v[0].x * mid, ct.snd + 6ll * mid, base.a) >= 0) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        lim[0] = lo;

        if (pl.v[0].x <= base.b) {
            printf("%lld .. inf\n", lim[0]);
        } else {
            lo = 0;
            hi = 2e11;
            while (lo < hi) {
                ll mid = lo + (hi-lo+1)/2;
                if (cmp(ct.fst + 6ll * pl.v[0].x * mid, ct.snd + 6ll * mid, base.b) < 0) {
                    lo = mid;
                } else {
                    hi = mid - 1;
                }
            }
            lim[1] = lo+1;

            printf("%lld .. %lld\n", lim[0], lim[1]);
        }
    }
}
