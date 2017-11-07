#include <bits/stdc++.h>
#define cout if (0) cout
 
// XXX without explanation marks untested functions
 
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back
 
// NOT STANDART FROM HERE
 
// area de calota 2.pi.R.h (h altura)
// volume de calota pi.h/6 * (3r^2 + h^2)
 
 typedef double cood;
 cood eps = 1e-8;
// tests for double were made with eps = 1e-8
 
double eps_d = 1e-8; // necessary even in integer geometry, should be eps otherwise
 
const double pi = acos(-1.);
 
inline ll sq (ll x)
{ return x*x; }
inline double sq (double x)
{ return x*x; }
 
struct vec { // vector
    // === BASIC ===
    cood x, y;
    vec () : x(0), y(0) {}
    vec (cood a, cood b) : x(a), y(b) {}
    friend ostream& operator<<(ostream& os, vec o);
 
    vec operator - (vec o)
    { return vec(x - o.x, y - o.y); }
    vec operator + (vec o)
    { return vec(x + o.x, y + o.y); }
    vec operator * (cood o)
    { return vec(x * o, y * o); }
    vec operator / (cood o)
    { return vec(x / o, y / o); }
    cood operator ^ (vec o)
    { return x * o.y - y * o.x; }
    cood operator * (vec o)
    { return x * o.x + y * o.y; }
 
    // positive is (*this)b is clockwise from (*this)a
    double angle (vec a, vec b)
    { return atan2((a-(*this))^(b-(*this)), (a-(*this))*(b-(*this))); }
 
    cood sq (vec o = vec())
    { return ((*this)-o)*((*this)-o); }
    double nr (vec o = vec())
    { return sqrt(sq(o)); }
 
    cood cross (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
    { return (b - a) ^ ((*this) - a); }
    int ccw (vec a, vec b) // which side is this from ab? (1 left, 0 over, -1 right)
    { cood o = cross(a, b); return (eps < o) - (o < -eps); } 
 
    int dir (vec a, vec b) // direction of (this)a relative to (this)b (-1 opposite, 0 none, 1 same)
    { cood o = ((*this) - a)*((*this) - b); return (eps < o) - (o < -eps); }
 
    cood inner (vec s, vec t) // (p-s)*(t-s) where p = this projected on st
    { return ((*this) - s) * (t - s); }
    vec proj (vec s, vec t) // projection of this point over line st
    { return s + (t - s)*(inner(s,t) / t.sq(s)); }
 
    vec rotate (double a) // rotate ccw by a (fails with ll)
    { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }
    vec rot90 () // rotate pi/2 ccw
    { return vec(-y, x); }
 
    // === ADVANCED ===
    // ordering that defines the compare method
    // used only there, change it accordingly
    // sorts increasing on y and, then increasing on x
    bool operator < (const vec & o) const {
        if (y != o.y)
            return y < o.y;
        return x < o.x;
    }
 
    // full ordering (ccw angle from this+(1,0), distance to this)
    // is a < b?
    // PRECISION : ok with double if norm in [-1e9,5e3]
    bool compare (vec a, vec b) {
        if (((*this) < a) != ((*this) < b))
            return (*this) < a;
        int o = ccw(a,b);
        if (o) return o > 0;
        return a.dir((*this),b) < 0;
    }
 
    // is this inside segment st? (tip of segment included, change for dr < 0 otherwise)
    bool in_seg (vec s, vec t)
    { return (ccw(s,t) == 0) && (dir(s,t) <= 0); }
 
    // squared distance from this to line defined by st
    double dist2_lin (vec s, vec t)
    { return double(::sq(cross(s,t))) / t.sq(s); }
    // squared distance from this to segment st
    double dist2_seg (vec s, vec t) 
    { return s.dir((*this),t) == t.dir((*this),s) ? dist2_lin(s,t) : min(sq(s),sq(t)); }
 
    // is this inside (borders included) the convex polygon v of size n?
    // if yes, prec is the vec that this on acw order from v[0] or 0 if there is no such
    // if not, prec is the predecessor of this when added to poly and succ is the sucessor
    // p should be a vector with [0..n-1]
    // n should be >= 2
    bool in_conv_poly (vec v[], int n, const vector<int> & p, int & prec, int & succ) {
        if (nr(v[0]) <= eps) {
            prec = 0;
            return 1;
        }
 
        if (n == 2) {
            if (in_seg(v[0],v[1]))
                return (prec = 1);
 
            if (ccw(v[0],v[1]) > 0) {
                prec = 1;
                succ = 0;
            } else if (ccw(v[0],v[1]) < 0) {
                prec = 0;
                succ = 1;
            } else {
                prec = succ = (v[0].dir((*this),v[1]) < 0);
            }
            return 0;
        }
         
        if (ccw(v[0],v[1]) > 0 || ccw(v[0],v[n-1]) < 0) {
        // case where v[0] is not removed
            // last diagonal before or over this
            int di = lower_bound(p.begin() + 1, p.end(), -1, [this,v] (int i, int j) {
                assert(j == -1);
                return ccw(v[0],v[i]) >= 0;
            }) - p.begin() - 1;
 
            // is this inside the polygon?
            prec = di;
            if (di == n-1) {
            // last segment
                if (ccw(v[0],v[n-1]) == 0 && ccw(v[n-2],v[n-1]) >= 0)
                    return 1;
            } else {
            // inside otherwise
                if (ccw(v[di],v[di+1]) >= 0)
                    return 1;
            }
 
            // last that stays before (or eq to) di
            prec = lower_bound(p.begin() + 1, p.begin() + di + 1, -1, [this,v] (int i, int j) {
                assert(j == -1);
                return ccw(v[i-1],v[i]) > 0;
            }) - p.begin() - 1;
 
            // first that stays after di
            succ = lower_bound(p.begin() + di + 1, p.end(), -1, [this,v,n] (int i, int j) {
                assert(j == -1);
                return ccw(v[(i+1)%n],v[i]) >= 0;
            }) - p.begin();
            if (succ == n) succ = 0;
        } else {
        // case where v[0] is removed
            // first diagonal before of over this
            // di is certainly not removed
            int di = lower_bound(p.begin() + 1, p.end() - 1, -1, [this,v] (int i, int j) {
                assert(j == -1);
                return ccw(v[0],v[i]) < 0;
            }) - p.begin();
 
            // first that stays (<= di)
            succ = lower_bound(p.begin(), p.begin() + di, -1, [this,v] (int i, int j) {
                assert(j == -1);
                return ccw(v[i+1],v[i]) >= 0;
            }) - p.begin();
 
            // last that stays (>= di)
            prec = lower_bound(p.begin() + di + 1, p.end(), -1, [this,v] (int i, int j) {
                assert(j == -1);
                return ccw(v[i-1],v[i]) > 0;
            }) - p.begin() - 1;
        }
        return 0;
    }
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }
 
struct lin { // line
    cood a, b, c; // a*x + b*y = c
 
    lin () {}
    lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
    lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}
 
    lin parll (vec p) // parallel to this through p
    { return lin(a, b, a * p.x + b * p.y); }
    lin perp ()
    { return lin(-b, a, c); }
 
    vec inter (lin o) {
        cood d = a * o.b - o.a * b;
        if (d < eps && -eps < d) throw 0; // parallel
        return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
    }
};
 
struct cir { // circle
    vec c; cood r;
 
    // borders included
    bool contains (vec w)
    { return c.sq(w) <= sq(r) + eps; }
    bool has_inter (cir o)
    { return c.sq(o.c) <= sq(r + o.r) + eps; }
    bool has_inter_lin (vec s, vec t)
    { return c.dist2_lin(s,t) <= sq(r) + eps_d; }
    bool has_inter_seg (vec s, vec t)
    { return c.dist2_seg(s,t) <= sq(r); }
 
    // borders not included
    bool contains (cir o)
    { return (o.r < r - eps && c.sq(o.c) < sq(r - o.r) - eps); }
 
    // ccw oriented area of arc from a to b
    double arc_area (vec a, vec b) {
        double ang = c.angle(a,b);
        return r*r*ang*.5;
    }
 
    // double only
    pair<vec,vec> inter_pts (cir o) {
        assert(has_inter(o) && !contains(o)); // fully contained case
        double d = c.nr(o.c);
        double a = (r*r + d*d - o.r*o.r) / (2.*d); // r*cos(ans,v,c.v)
        double h = sqrt(r*r - a*a);
        if (h != h) h = 0;
        vec p = o.c - c;
        return pair<vec,vec>(c + p*(a/d) + (p.rot90()*(h/d)), c + p*(a/d) - (p.rot90()*(h/d)));
    }
 
    // double only XXX careful precision
    pair<vec,vec> inter_pts (vec s, vec t) { 
        assert(has_inter_lin(s,t));
        double h2 = c.dist2_lin(s,t);
        double d = sqrt(c.sq(t) - h2);
        if (d != d) d = 0;
        vec p = (s-t);
        vec m = t + p*(d/p.nr());
        vec m_b = t - p*(d/p.nr());
        if (m_b.sq(c) < m.sq(c))
            m = m_b;
 
        d = sqrt(r*r - h2);
        if (d != d) d = 0;
        pair<vec,vec> res(m + p*(d/p.nr()), m - p*(d/p.nr()));
        if (res.first.sq(t) > res.second.sq(t))
            swap(res.first, res.second);
        return res;
    }
 
    // double only XXX not tested
    // signed area of intersection of this with triangle (this.c,a,b)
    double inter (vec a, vec b) {
        cout << c << " with " << a << "," << b << ": ";
        double res = 0.;
        bool inv = 0;
        if (contains(b)) {
            swap(a,b);
            inv = 1;
            cout << "[inv] ";
        }
 
        if (contains(b)) {
            cout << "contains both";
            res = c.cross(a,b)*.5;
        } else if (contains(a)) {
            cout << "contains " << a;
            pair<vec,vec> rt = inter_pts(a,b);
            cout << endl << "[[" << rt.first << " " << rt.second << endl;
            vec q = rt.first;
            if (!q.in_seg(a,b) || (a.sq(q) <= eps && rt.second.in_seg(a,b)))
            //if (rt.second.dist2_seg(a,b) < q.dist2_seg(a,b))
                q = rt.second;
            cout << " inter at " << q;
 
            res += c.cross(a,q)*.5;
            res += arc_area(q,b);
        } else if (has_inter_seg(a, b)) {
            cout << "inter seg";
            pair<vec,vec> rt = inter_pts(b,a);
 
            res += arc_area(a,rt.first);
            res += c.cross(rt.first,rt.second)*.5;
            res += arc_area(rt.second,b);
        } else {
            cout << "arc only";
            res += arc_area(a,b);
        }
 
        if (inv) res = -res;
        cout << " = " << res << endl;
        return res;
    }
 
    double area (vec a, vec b) {
        double aa = c.nr(a), bb = c.nr(b), cc = sqrt(c.dist2_seg(a,b));
        if (aa <= r + eps && bb <= r + eps) return .5*abs((a-c)^(b-c));
        if (cc >= r - eps) return .5*abs(r*r*c.angle(a,b));
 
        if (aa > bb + eps) { swap(a,b); swap(aa,bb); }
        double A = a.sq(b), B = 2.*((a-b)*(b-c)), C = b.sq(c) - r*r;
        double t = B*B-4*A*C;
        if (abs(t) <= eps) t = 0;
        else t = sqrt(t);
        double x1 = .5*(-B-t)/A, x2 = .5*(-B+t)/A;
        vec p1 = a*x1 + b*(1-x1), p2 = a*x2 + b*(1-x2);
 
        if (aa < r - eps) return area(a,p1) + area(p1,b);
        return area(a,p2) + area(p2,p1) + area(p1,b);
    }
 
    // double only XXX not tested
    // signed area of intersection of this with polygon
    double inter (vector<vec> & p) {
        double res = 0;
        for (int i = 0; i < p.size(); i++) {
            //res += area(p[i],p[(i+1)%p.size()]) * c.ccw(p[i],p[(i+1)%p.size()]);
            res += inter(p[i],p[(i+1)%p.size()]);
        }
 
        return res;
    }
};
 
// do the segments ab and cd intersect? (borders included) XXX
bool inter_seg (vec a, vec b, vec c, vec d) {
    if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
        return true;
    return (c.ccw(a, b) * d.ccw(a, b) == -1 && a.ccw(c, d) * b.ccw(c, d) == -1);
}
 
// squared distance from segments ab and cd XXX
double dist2_seg (vec a, vec b, vec c, vec d)
{ return inter_seg(a,b,c,d) ? 0. : min({ a.dist2_seg(c,d), b.dist2_seg(c,d), c.dist2_seg(a,b), d.dist2_seg(a,b) }); }
 
// brd = do points on the border belong to convex?
// computes convex hull of given vector (inplace)
// returns size of convex hull
int graham (vec v[], int n, int brd) {
    for (int i = 1; i < n; i++) {
        if (v[i].x < v[0].x || (v[i].x == v[0].x && v[i].y < v[0].y))
            swap(v[0], v[i]);
    }
 
    sort(v+1, v+n, [v] (vec a, vec b) {
        int o = b.ccw(v[0], a);
        if (o) return (o == 1);
        return v[0].sq(a) < v[0].sq(b);
    });
 
    if (brd) {
        int s = n-1;
        while (s > 1 && v[s].ccw(v[s-1],v[0]) == 0)
            s--;
        for (int i = s; i < n - 1 - (i - s); i++)
            swap(v[i], v[n-1-(i-s)]);
    }
 
    int s = 0;
    for (int i = 0; i < n; i++) {
        if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
        while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= brd)
            s--;
        v[s++] = v[i];
    }
 
    return s;
}
 
const int N = 1e2+7;
 
int n;
double r;
vector<vec> v;
double x[2], y[2];
 
double solve (double x) {
    double lo = 200, hi = -100.;
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n;
        lin ln(v[i],v[j]);
        vec it(x, (ln.c - ln.a*x)/ln.b);
        cout << it << " ";
        if (it.in_seg(v[i],v[j]) && it.y == it.y && abs(it.y) < 200) {
            lo = min(lo, it.y);
            hi = max(hi, it.y);
        }
 
        if (abs(v[i].x - x) <= eps_d) {
            cout << v[i] << "! ";
            lo = min(lo, v[i].y);
            hi = max(hi, v[i].y);
        }
    }
    hi = min(hi, 200.); lo = max(lo, -100.);
    cout << x << " [" << lo << " " << hi << "]" << endl;
 
    int ts = 60;
    while (ts--) {
        double q1 = (lo+lo+hi)/3;
        double q2 = (lo+hi+hi)/3;
 
        double r1 = abs(cir({ vec(x,q1), r }).inter(v));
        double r2 = abs(cir({ vec(x,q2), r }).inter(v));
 
        if (r1 < r2)
            lo = q1;
        else
            hi = q2;
    }
 
    return abs(cir({ vec(x,lo), r }).inter(v));
}
 
int main () {
 
    while (scanf("%d %lf", &n, &r) != EOF) {
        cout << n << endl;
        v = vector<vec>(n);
         
        x[0] = 200;
        x[1] = -100;
 
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &v[i].x, &v[i].y);
            cout << v[i] << " ";
 
            x[0] = min(x[0],v[i].x);
            x[1] = max(x[1],v[i].x);
        }
        cout << endl;
 
        double lo = x[0], hi = x[1];
        //int ts = 60;
        int ts = 50;
        while (ts--) {
            double q1 = (lo+lo+hi)/3;
            double q2 = (lo+hi+hi)/3;
             
            if (solve(q1) < solve(q2))
                lo = q1;
            else
                hi = q2;
        }
 
        double res = solve(lo);
        for (int i = 0; i < n; i++)
            res = max(res, abs(cir({ v[i], r }).inter(v)));
 
        printf("%.20f\n", res);
    }
}
