#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
typedef long double cood;
typedef complex<cood> point;
const cood pi = acos(-1.0);
const cood eps = 1e-9;

inline cood x(const point& a)
{ return real(a); }
inline cood y(const point& a)
{ return imag(a); }
inline cood inner(const point& a,const point& b)
{ return x(a)*x(b) + y(a)*y(b); }
inline cood cross(const point& a,const point& b)
{ return x(a)*y(b) - y(a)*x(b); }
inline cood area(const point& a,const point& b,const point& c)
{ return cross(b-a, c-a); }

cood ans, dist, ix, iy, r[2], d[2], h, ang;
point c[2], p[2], dir, pvt;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> ix >> iy >> r[0];
    c[0] = point(ix,iy);
    cin >> ix >> iy >> r[1];
    c[1] = point(ix,iy);

    if(r[0] < r[1])
        swap(r[0],r[1]), swap(c[0], c[1]);
    dist = abs(c[1]-c[0]);
    if(dist > eps)
        dir = (c[1]-c[0])/dist;

    if(dist + eps > r[0] + r[1])
        ans = cood(0.0);
    else if(dist + r[1] < r[0] + eps)
        ans = pi*r[1]*r[1];
    else
    {
        cood ang = acos((r[1]*r[1]+dist*dist-r[0]*r[0])/(2.*r[1]*dist)),
               s = ang*r[1]*r[1], t = r[1]*r[1]*sin(ang)*cos(ang);
        ans = s - t;
        ang = acos((r[0]*r[0]+dist*dist-r[1]*r[1])/(2.*r[0]*dist)),
          s = ang*r[0]*r[0], t = r[0]*r[0]*sin(ang)*cos(ang);

        ans += s - t;
    }
    cout << setprecision(20) << ans << '\n';
}
