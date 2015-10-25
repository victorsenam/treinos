#include <bits/stdc++.h>

using namespace std;

typedef double num;

const double eps = 1e-11;

struct vect {
    num x, y;
    
    vect operator + (const vect & b) const {
        vect res;
        res.x = x + b.x;
        res.y = y + b.y;
        return res;
    }

    vect operator - (const vect & b) const {
        vect res;
        res.x = x - b.x;
        res.y = y - b.y;
        return res;
    }

    // dot product
    num operator * (const vect & b) const
    { return ((x*b.x)+(y*b.y)); }

    // scalar product
    vect operator * (num b) const {
        vect res;
        res.x = x*b;
        res.y = y*b;
        return res;
    }

    vect over (const vect & b) const 
    { return b*(((*this)*b)/(b*b)); }
};

num har, hpr;
vect a, b, c;
vect ps, pt;

void succ () {
    printf("YES\n%.10lf %.10lf\n%.10lf %.10lf\n", ps.x, ps.y, pt.x, pt.y);
}

num area (vect c, vect b, vect a) {
    a = c-a;
    b = c-b;

    num res = 0;
    if (b*b > eps) {
        vect h = (a-a.over(b));
        res = (sqrt(h*h)*sqrt(b*b))/2;
    }

    return res;
}

bool bb (vect a, vect b, vect c) {
    vect va = b-a;
    vect vb = c-b;
    num la = sqrt(va*va);
    num lb = sqrt(vb*vb);

    num lo = max(0.0, la-hpr);
    num hi = min(la+lb-hpr, la);

    ps = a;
    pt = a;
    area(ps, pt, b);
    
    while (hi - lo > eps) {
        num fs = lo + (hi-lo)/3.0;
        num ss = lo + (hi-lo)*2.0/3.0;
        ps = a + va*(fs/la);
        pt = b + vb*((fs+hpr-la)/lb);

        num pa = area(ps, pt, b);

        vect qs = a + va*(ss/la);
        vect qt = b + vb*((ss+hpr-la)/lb);
        num qa = area(qs, qt, b);

        if (abs(har - pa) > abs(har - qa))
            lo = fs;
        else
            hi = ss;
    }

    if (abs(area(ps, pt, b) - har) < eps)
        return 1;
    return 0;
}

int main () {
    scanf("%lf %lf %lf %lf %lf %lf",
        &a.x, &a.y,
        &b.x, &b.y,
        &c.x, &c.y
    );

    har = area(a, b, c)/2.0;
    hpr = sqrt((a-b)*(a-b)) + sqrt((b-c)*(b-c)) + sqrt((c-a)*(c-a));
    hpr /= 2.0;

    if (bb(a, b, c))
        succ();
    else if (bb(c, a, b))
        succ();
    else if (bb(b, c, a))
        succ();
    else
        printf("NO\n");
}
