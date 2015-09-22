#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef double cood;
typedef complex<cood> point;
typedef long long hsh;
typedef int node;
typedef int edge;
const cood tau = 2*acos(-1.0);
const cood fix = 0.25*sqrt(3);
cood in;
point h[6];
point dir;
int hs, ans;

inline cood x(point& a)
{ return real(a); }
inline cood y(point& a)
{ return imag(a); }

inline cood area(point a, point b, point c)
{
    return fabs(
            x(a)*(y(b)-y(c))+
            y(a)*(x(c)-x(b))+
            x(b)*y(c)-x(c)*y(b)
            );
}

int main()
{
    h[hs++] = point(0,0);
    dir = point(1,0);
    for(int i=0;i<5;i++)
    {
        cin >> in;
        h[hs] = h[hs-1] + dir*in; hs++;
        dir *= polar(1.0, tau/6.0);
    }
    in = 0.0;
    for(int i=1;i<hs-1;i++)
        in += 0.5*area(h[0],h[i],h[i+1]);
    printf("%.0lf\n", in/fix);
}
