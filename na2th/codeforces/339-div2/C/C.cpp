#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num;
typedef double cood;
typedef complex<cood> point;
const cood PI = acos(-1.0);
const cood eps = 1e-9;

const int N = 1e5;
point p[N], c;
cood ix, iy;

inline cood x(point a) { return real(a); }
inline cood y(point a) { return imag(a); }
inline cood inner(point a, point b)
{ return x(conj(a)*b); }
point pSproj(point a,point b, point c)
{
    if(abs(a-b) < eps) return a;
    cood t = inner(c-a,b-a)/norm(b-a);
    if(t < 0) return a;
    if(t > 1) return b;
    return a + t*(b-a);
}
int main()
{
    int n;
    ios::sync_with_stdio(false);
    cin >> n >> ix >> iy;
    c = point(ix, iy);
    for(int i=0;i<n;i++)
    {
        cin >> ix >> iy;
        p[i] = point(ix, iy);
    }
    double big = 0, small = 1e9;
    for(int i=0;i<n;i++)
    {
        big  = max(big,    abs(p[i]-c));
        small = min(small, abs(pSproj(p[i],p[(i+1)%n],c)-c));
    }
    cout << setprecision(20) << PI*big*big - PI*small*small << endl;
}
