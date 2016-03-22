#include <bits/stdc++.h>
#define mp make_pair

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

typedef long double cood;
typedef complex<cood> point;
const int N = 101;
const int M = 3*N*N;
const cood eps = 1e-12;

int i, j, k, n;
point p[N];
cood a, xin, yin, lo, hi, s, w, w_c;

inline cood x(point a){ return real(a); }
inline cood y(point a){ return imag(a); }
inline cood inner(point a,point b){ return real(conj(a)*b); }
inline cood cross(point a,point b){ return imag(conj(a)*b); }

int main () {
    cin >> a >> n;
    for(i=0;i<n;i++){
        cin >> xin >> yin;
        p[i] = point(xin, yin);
    }
    if(fabsl(cood(1)-a) < eps){
        cout << setprecision(20) << cood(1e3) << endl;
        return 0;
    }
    w = cood(0);
    for(i=1;i<n-1;i++) w += fabsl(cross(p[i]-p[0],p[i+1]-p[0]));
    lo = 2; hi = 1e3;
    while(fabsl(hi-lo) > eps){
        s = cood(.5)*(hi+lo);
        w_c = 0.;
        for(i=0;i<n;i++){
            j = (i+1)%n, k = (i+n-1)%n;
            point pa = p[i] + (p[j]-p[i])/s,
                  pb = p[i] + (p[k]-p[i])/s;
            w_c += fabsl(cross(pb-p[i],pa-p[i]));
        }
        if((cood(1)-a)*w > w_c) hi = s;
        else lo = s;
    }
    cout << setprecision(20) << lo << endl;
}
