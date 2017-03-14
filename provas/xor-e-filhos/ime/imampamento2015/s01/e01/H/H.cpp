#include<bits/stdc++.h>
using namespace std;
typedef double cood;
typedef complex<cood> point;
const double eps = 1e-9;
const double tau = 2*acos(-1.0);

cood ax, ay, bx,by, cx,cy;

inline cood x(point a)
{ return real(a); }
inline cood y(point a)
{ return imag(a);}
cood inner(point a, point b)
{ return x(a)*x(b) + y(a)*y(b); }
cood cross(point a, point b)
{ return x(a)*y(b) - y(a)*x(b); }

cood bSearch(point a, point b, point c)
{
    cood lans = DBL_MAX, ans = 0.0,
         hi = 1.0, lo = 0.0;
    while( fabs(hi-lo) > eps )
    {
        cood r = 0.5*(hi+lo);
        point guess = a + r*(b-a);
        ans = 2*abs(guess-a) + 2*abs(guess-b) + abs(guess-c);
        if( abs(guess-b) < abs(guess-a) )
            lo = r;
        else
            hi = r;
        lans = ans;
    }
    return ans;
}

inline point intersect(point a, point b, point c, point d)
{ return (a + (b-a)*(cross(c-a,d-c)/cross(b-a,d-c))) ;}

point circumcenter(point a, point b, point c)
{
    point ab = 0.5*(a+b) + (b-a)*polar(1.0, 0.25*tau),
          bc = 0.5*(b+c) + (c-b)*polar(1.0, 0.25*tau);
    return intersect(0.5*(a+b), ab, 0.5*b+c, bc);
}

int main()
{
    while( scanf("%lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy) != EOF && (ax>0||bx>0||cx>0||ay>0||by>0||cy>0) )
    {
        cood ans;
        point pa (ax,ay),
              pb (bx, by),
              pc (cx,cy), guess;
        ans = bSearch(pa, pb, pc);
        ans = min(ans, bSearch(pb,pc,pa));
        ans = min(ans, bSearch(pc,pa,pb));
        printf("%.8lf\n", ans);
    }
}
