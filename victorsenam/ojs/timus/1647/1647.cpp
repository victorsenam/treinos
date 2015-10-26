#include <bits/stdc++.h>

using namespace std;

typedef double num;

const double eps = 1e-11;

struct vect {
    num x, y;

    vect() {}
    vect(num px, num py) : x(px), y(py) {}

    inline vect operator + (const vect & b) const
    { return vect(x+b.x, y+b.y); }

    inline vect operator - (const vect & b) const
    { return vect(x-b.x, y-b.y); }

    inline num operator * (const vect & b) const
    { return x*b.x + y*b.y; }
    
    inline num operator ^ (const vect & b) const
    { return x*b.y - y*b.x; }

    inline vect operator * (num al) const
    { return vect(x*al, y*al); }

    inline vect operator / (num al) const
    { return vect(x/al, y/al); }

    inline vect proj (const vect & b) const
    { return b*(((*this)*b)/(b*b)); }

    inline void print ()
    { printf("%.10lf %.10lf\n", x, y); }

    inline num norm ()
    { return sqrt((*this)*(*this)); }

    inline vect unit ()
    { return ((*this)/((*this).norm())); }

};

vect v[3];
vect s, t;
num pr, ar;

num area (vect a, vect b, vect c) {
    if (abs((a-b)^(a-c)) < eps)
        return 0.0;

    vect ab = b-a;
    vect ac = c-a;
    return (ab.norm())*((ac-ac.proj(ab)).norm())/2.0;
}

num go (vect v, vect da, num la, vect db, num lb, num val) {
    vect a = v + da*(pr-val);
    vect b = v + db*val;

    return area(v, a, b);
}

bool solve (vect v, vect a, vect b) {
    vect da = (a-v);
    vect db = (b-v);
    num la = da.norm();
    num lb = db.norm();
    da = da/la;
    db = db/lb;

    num lo = max(0.0, pr-la);
    num hi = min(lb, pr);

    while ( hi - lo > eps ) {
        num q1 = lo + (hi-lo)/3.0;
        num q2 = lo + (hi-lo)*2.0/3.0;

        num ra = go(v, da, la, db, lb, q1);
        num rb = go(v, da, la, db, lb, q2);

        if (abs(ra-ar) > abs(rb-ar))
            lo = q1;
        else
            hi = q2;
    }

    num res = go(v, da, la, db, lb, lo);
    if (abs(res - ar) < eps) {
        s = v + da*(pr-lo);
        t = v + db*lo;

        return 1;
    } else  {
        return 0;
    }
}

void succ () {
    printf("YES\n");
    s.print();
    t.print();
    exit(0);
}

int main () {
    for (int i = 0; i < 3; i++)
        scanf("%lf %lf", &v[i].x, &v[i].y);

    ar = (area(v[0], v[1], v[2]))/2.0;
    pr = ((v[1]-v[0]).norm() + (v[2]-v[1]).norm() + (v[0]-v[2]).norm())/2.0;

    if (solve(v[0], v[1], v[2]))
        succ();

    if (solve(v[1], v[2], v[0]))
        succ();

    if (solve(v[2], v[0], v[1]))
        succ();

    printf("NO\n");
}
