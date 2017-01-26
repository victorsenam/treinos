#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long ll;

// ## complexity ##
// last line in comments means complexity
// time | space
// standart: O(1) | O(1)
#define vec vect<cood>

#define tmpl template<typename cood>
const double pi = acos(-1.);

// ## formulas ##
// area da calota : 2 * pi * r * h
// volume da calota : pi * h * (3*r^2 + h^2) / 6

// ## about eps ##
// many functions recieve an optional parameter eps
// when dealing with floating point numbers, eps is the size of a point
// if you want points to be considered as existant, eps should be positive
// otherwise, eps should be negative

// ## position functions ##
// functions that refer to position (inside, contains, intersects, etc)
// and return an integer follow a standart
// examples are based the return of pl.inside(p) given a poly pl and a 
// vect p
// 1 : respects fully (eg: p is fully strictly inside pl)
// 0 : respects only for a point (eg: p is on the border of pl)
// -1 : does not respect (eg: p is outside of pl)

template<typename cood> inline bool lt (cood a, cood b, cood eps = 0)
{ return (a - b < eps); }
template<> inline bool lt (ll a, ll b, ll eps)
{ return (a < b + eps); }

template<typename cood> inline bool lte (cood a, cood b, cood eps = 0)
{ return (a - b <= eps); }
template<> inline bool lte (ll a, ll b, ll eps)
{ return (a <= b + eps); }

template<typename cood> struct vect {
    cood x,y;
    
    // constructors
    vec () {}
    vec (cood a, cood b) : x(a), y(b) {}

    // basics
    inline bool operator < (vec ot) const // lex compare
    { return (x < ot.x || (x == ot.x && y < ot.y)); }

    // transforming
    inline vec operator - (vec ot) const
    { return vec(x - ot.x, y - ot.y); }
    inline vec operator + (vec ot) const
    { return vec(x + ot.x, y + ot.y); }
    inline vec operator * (cood a) const
    { return vec(x * a, y * a); }
    inline vec operator / (cood a) const
    { return vec(x / a, y / a); }
    inline vect<double> rotate (double ang) const // counter-clockwise
    { return vect<double>(cos(ang) * x - sin(ang) * y, sin(ang) * x + cos(ang) * y); }

    // math
    inline cood operator ^ (vec ot) const // cross
    { return x * ot.y - y * ot.x; }
    inline cood operator * (vec ot) const // inner
    { return x * ot.x + y * ot.y; }
    inline cood sq (vec ot = vec(0,0)) const // squared 2-norm (and distance)
    { return ((*this)-ot)*((*this)-ot); }
    inline double nr (vec ot = vec(0,0)) const // 2-norm (and distance)
    { return sqrt(sq(ot)); }
    inline cood ar (vec a, vec b) const // oriented area (positive if b is to the left of a)
    { return (a-(*this))^(b-(*this)); }

    // XXX: not a full comparsion operator, use compare for ordering
    // counter-clockwise comparsion (to the left means greater)
    // returns -1 if a < b [a->b is counter-clockwise]
    // returns 0 if a == b [colinear]
    // returns 1 if a > b [a->b is clockwise]
    int left (vec a, vec b, cood eps = 0) const
    { cood o = ar(a, b); return (o < -eps) - (o > eps); }

    // divide the plane by anc
    // returns 0 if the counter-clockwise angle between anc and this is x s.t. 0 <= x < pi
    // returns 1 otherwise (pi <= x < 2pi)
    inline bool halfplane (vec anc = vec(1,0), cood eps = 0) const {
        int o = vec(0,0).left(anc, *this, eps);
        if (o == 0)
            return (*this)*(anc) < 0;
        return (o == 1);
    }

    // full comparsion
    // orders by clockwise order starting from the (0,-1) direction (upwards)
    // settles draws by proximity to this point
    bool compare (vec ot, vec anc = vect<cood>(1,0), cood eps = 0) const {
        bool s[2] = {halfplane(anc, eps), ot.halfplane(anc, eps)};
        if (s[0] != s[1])
            return s[0] < s[1];

        int pr = vec(0,0).left((*this), ot, eps);
        if (pr)
            return (pr < 0);
        return sq() < ot.sq();
    }
};

const int N = 1e5+7;

int n;
vect<ll> v[N];
vect<ll> o;
int f[2][2];

vect<ll> q[4][N];
int qs[4];

int main () {
    scanf("%d", &n);
    scanf("%lld %lld", &o.x, &o.y);

    n--;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &v[i].x, &v[i].y);
        v[i] = v[i] - o;

        if (v[i].x >= 0 && v[i].y >= 0)
            q[0][qs[0]++] = v[i];
        else if (v[i].x <= y && v[i].y <= 0)
            q[2][qs[2]++] = v[i];
        else if (v[i].x > 0 && v[i].y < 0)
            q[3][qs[3]++] = v[i];
        else
            q[1][qs[1]++] = v[i];
    }

    o = vect<ll>(0,0);

    sort(v, v+n, [] (const vect<ll> & a, const vect<ll> & b) {
        return a.compare(b, vect<ll>(0,1));
    });

    // separei os quadrante, só fazer

    int j = 0;
    for (int i = 0; i < n; i++) {
        if (v[i].x > 0 || v[i].y < 0) break;
        int lf = 0;
        while (i + lf < n && o.left(v[i], v[i+lf]) == 0) lf++;
        j = max(i+lf+1, j);
        while (j < n && o.left(v[i], v[j]) < 0) j++;
        int rg = 0;
        while (j + rg < n && o.left(v[i], v[j+rg]) == 0) rg++;

        debug("%d-%d-%d-%d\n", i, i+lf, j, j+rg);

        r[0] = min(r[0], j-(i+lf)+1);
        r[1] = min(r[1], j+rg-i+1);
        i += lf;
        j += rg;
    }

    printf("%d %d\n", r[0], r[1]);
}
