#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef double cood;
typedef complex<cood> point;
const int MP  = 202;
const cood tau = (2*acos(-1.0));
const cood eps = 1e-9;

point pol0[MP], pol1[MP];

inline cood x(const point& a)
{ return real(a); }
inline cood y(const point& a)
{ return imag(a); }
inline cood inner(const point& a, const point& b)
{ return x(a)*x(b) + y(a)*y(b); }
inline cood cross(const point& a, const point& b)
{ return x(a)*y(b) - y(a)*x(b); }
inline cood area(const point& a,const point& b, const point& c)
{ return cross(b-a,c-a); }

// Projeta e no segmento ab
point pSproj(point c, point a, point b)
{
    if(abs(a-b)<eps) return a;
    cood t = inner(c-a,b-a)/norm(b-a);
    if(t<0) return a;
    if(t>1) return b;
    return a + t*(b-a);
}

cood pSdist(point c, point a, point b)
{ return abs(c-pSproj(c,a,b)); }

int main()
{
    int is, os, tc;
    scanf("%d", &tc);
    while( tc-- )
    {
        scanf("%d", &is);
        for(int i=0;i<is;i++)
        {
            cood ix, iy;
            scanf("%lf %lf", &ix, &iy);
            pol0[i] = point (ix, iy);
        }
        scanf("%d", &os);
        for(int i=0;i<os;i++)
        {
            cood ix, iy;
            scanf("%lf %lf", &ix, &iy);
            pol1[i] = point(ix,iy);
        }
        cood d = DBL_MAX;
        for(int i=0;i<is;i++)
        for(int j=0;j<os;j++)
            d = min(d, pSdist(pol0[i],pol1[j],pol1[(j+1)%os]));

        for(int j=0;j<os;j++)
        for(int i=0;i<is;i++)
            d = min(d, pSdist(pol1[j],pol0[i], pol0[(i+1)%is]) );

        printf("%.9lf\n", 0.5*d);
    }
}
