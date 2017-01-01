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

const int N = 20;

int n, tc;
vect<ll> v[N];
ll c[N], l[N];

ll r[4];
double lf;

double solve (int msk) {
    poly<ll> pl;
    for (int i = 0; i < n; i++) {
        if (msk&(1<<i)) continue;
        pl.v.push_back(v[i]);
    }

    if (pl.v.size() <= 1)
        return 0.;

    if (pl.v.size() > 2)
        pl.graham();

    double res = 0.;
    for (int i = 0; i < pl.v.size(); i++)
        res += pl.v[i].norm(pl.v[(i+1)%pl.v.size()]);
    return res;
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; i++)
            scanf("%lld %lld %lld %lld", &v[i].x, &v[i].y, &c[i], &l[i]);

        r[0] = INT_MAX;

        for (int msk = 1; msk < (1<<n); msk++) {
            double len = solve(msk);
            ll cov = 0;
            ll val = 0;
            for (int i = 0; i < n; i++) {
                if ((1<<i)&msk) {
                    val += c[i];
                    cov += l[i];
                }
            }

            if (len <= cov) {
                if (val > r[0]) continue;
                if (val == r[0] && __builtin_popcount(msk) >= __builtin_popcount(r[1])) continue;
                r[0] = val;
                r[1] = msk;
                lf = cov - len;
            }
        }

        if (tc)
            printf("\n");
        printf("Forest %d\n", ++tc);
        printf("Cut these trees:");
        for (int i = 0; i < n; i++)
            if ((1<<i)&r[1])
                printf(" %d", i+1);
        printf("\n");
        printf("Extra wood: %.2f\n", lf);
    }
}
