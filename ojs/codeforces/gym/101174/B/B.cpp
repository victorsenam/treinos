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

vect<ll> q[9][N];
int qs[9];

int getclass (const vect<ll> & a) {
    int r = ((a.y > 0) + (a.y >= 0));
    r *= 3;
    r += ((a.x > 0) + (a.x >= 0));
    return r;
}

int main () {
    scanf("%d", &n);
    scanf("%lld %lld", &o.x, &o.y);

    n--;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &v[i].x, &v[i].y);
        v[i] = v[i] - o;

        q[getclass(v[i])][qs[getclass(v[i])]++] = v[i];
    }

    o = vect<ll>(0,0);
    for (int i = 0; i < 9; i++) {
        sort(q[i], q[i]+qs[i], [] (const vect<ll> & a, const vect<ll> & b) {
            return (o.left(a,b) == -1);
        });
        
        /*
        printf("%d:", i);
        for (int j = 0; j < qs[i]; j++)
            printf(" (%d,%d)", q[i][j].x, q[i][j].y);
        printf("\n");
        */
    }

    int r[2] = {
        min(qs[6]+qs[7]+qs[8], qs[2]+qs[5]+qs[8]),
        max(qs[6]+qs[7]+qs[8]+qs[3]+qs[4]+qs[5], qs[2]+qs[5]+qs[8]+qs[1]+qs[4]+qs[7])
    };

    int j = 0;
    for (int i = 0; i < qs[6];) {
        int lf = 0;
        while (i + lf < qs[6] && o.left(q[6][i+lf], q[6][i]) == 0)
            lf++;
        while (j < qs[2] && o.left(q[6][i], q[2][j]) == -1)
            j++;
        int rg = 0;
        while (j + rg < qs[2] && o.left(q[6][i], q[2][j+rg]) == 0)
            rg++;

        r[0] = min(r[0], i+qs[2]-j-rg+qs[5]+qs[7]+qs[8]);
        r[1] = max(r[1], i+lf+qs[2]-j+qs[5]+qs[7]+qs[8]);
        i += lf;
    }

    printf("%d %d\n", r[0]+1, r[1]+1+qs[4]);
}
