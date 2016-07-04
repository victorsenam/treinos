#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef int64_t ll;
template<typename T> inline void _max(T& a, T b){ a = max(a,b); }
template<typename T> inline void _min(T& a, T b){ a = min(a,b); }

typedef double cood;
typedef complex<cood> point;

const int   N  = 5000;
const cood PI  = acos(-1.0);
const cood eps = 1e-9;

set<pair<int,int>> filter;
point P[N], trg[N][3];

cood inner(point a, point b) { return real(b*conj(a)); }
cood cross(point a, point b) { return imag(b*conj(a)); }
point intersect(point a, point b, point c, point d)
{ return c + (d-c)*cross(a-c,b-a)/cross(d-c,b-a); }

int n, ok;
int main(){
    ok = 1;
    scanf(" %d", &n);
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            int x, y;
            scanf(" %d%d", &x, &y);
            trg[i][j] = point(x,y);
            filter.insert(mp(x,y));
        }
    }
    for(int i=0;i<n;i++){
        point m0 = .5*(trg[i][0] + trg[i][1]),
              m1 = .5*(trg[i][1] + trg[i][2]),
              d0 = .5*(trg[i][1] - trg[i][0]),
              d1 = .5*(trg[i][2] - trg[i][1]),
              center = intersect(m0, m0 + d0*polar(1.,.5*PI), m1, m1 + d1*polar(1.,.5*PI));
        cood r = abs(trg[i][0] - center);
        int cnt = 0;
        for(auto p: filter)
            cnt += (abs(point(p.first, p.second) - center) < r + eps);
        ok &= (cnt == 3);
    }
    if(ok) puts("YES");
    else puts("NO");
}
