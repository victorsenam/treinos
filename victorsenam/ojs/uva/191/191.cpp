#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;
//typedef ll cood;

template<typename cood=ll> struct vect {
    cood x,y;
    
    vect<cood> () {}
    vect<cood> (cood a, cood b) : x(a), y(b) {}

    inline vect<cood> operator - (const vect<cood> & ot) const
    { return vect<cood>(x - ot.x, y-ot.y); }
    inline vect<cood> operator + (const vect<cood> & ot) const
    { return vect<cood>(x + ot.x, y + ot.y); }


    inline cood operator * (const vect<cood> & ot) const // cross
    { return y * ot.x - x * ot.y; }
    inline cood operator ^ (const vect<cood> & ot) const // inner
    { return x * ot.x + y * ot.y; }

    inline cood sq () const
    { return (*this)^(*this); }
    inline cood norm () const
    { return sqrt(sq()); }

    inline cood orient (const vect<cood> & a, const vect<cood> & b) const
    { return ((*this)-a)*((*this)-b); }
    
    // position of vector relative to convex polygon
    // poly : convex polygon given by sequence of vectors ordered by angle
    //        (clockwise or counter-clockwise)
    // return -1 if outside, 0 if in border and 1 if inside
    int position (const vector<vect<cood> > & poly) const {
        int n = poly.size();
        cood anc = orient(poly[n-1], poly[0]);
        if (anc > 0) anc = 1;
        else if (anc < 0) anc = -1;
        else return 0;

        for (int i = 0; i < n-1; i++) {
            cood rel = anc*orient(poly[i], poly[i+1]);
            if (rel == 0) return 0;
            else if (rel < 0) return -1;
        }

        return 1;
    }
};

template<typename cood=ll> struct line {
    vect<cood> s,t;

    line<cood> () {}
    line<cood> (vector<cood> a, vector<cood> b) : s(a), t(b) {}
    
    inline vect<cood> dir () const
    { return t - s; }

    inline vect<double> intersect (const line<cood> & ot) const {

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

        if (v.s.position({a[0], a[1], a[2], a[3]}) >= 0 || v.t.position({a[0], a[1], a[2], a[3]}) >= 0) {
            printf("T\n");
            continue;
        }

        for (int i = 0; i < 4; i++) {
            vect<double> 
        }

        printf("F\n");
    }
}
