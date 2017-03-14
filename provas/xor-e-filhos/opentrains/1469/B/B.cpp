#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
using namespace std;
typedef int64_t ll;
typedef long double cood;
typedef complex<cood> point;

const int N = 200;
const cood eps = 1e-9;

point s, c[N];
cood u[N], v;
vector<pair<cood, cood>> intervals, aux;

cood x(point a) { return real(a); }
cood y(point a) { return imag(a); }
cood inner(point a, point b) { real(conj(a)*b); }
cood cross(point a, point b) { imag(conj(a)*b); }
point intersect(point a, point b, point c, point d)
{ return c + (d-c)*cross(a-c,b-a)/cross(d-c,b-a); }
point proj(point a, point b, point c)
{ return a + (b-a)/norm(b-a)*inner(c-a,b-a); }

bool dinner(point g, int i){
    point d = (g-s)/abs(g-s);
    cood lo = 0, hi = abs(g-s)/v;
    while(fabs(hi-lo) > eps){
        cood _x = fabs(hi-lo)/3.;
        if(abs(s + (lo+_x)*v*d - c[i]) - u[i]*(lo+_x) < 
           abs(s + (hi-_x)*v*d - c[i]) - u[i]*(hi-_x)   )
            hi -= _x;
        else lo += _x;
    }
    return (abs(s + lo*v*d - c[i]) - u[i]*lo) <= eps;
}

pair<cood, cood> solve(cood l, cood r, int i){
    if(abs(c[i]-point({l,0})) > abs(c[i]-point({r,0}))) swap(l,r);
    cood lo = l, hi = r;
    while(fabs(hi-lo) > eps) {
        cood mid = .5*(lo+hi);
        if(dinner({mid,0},i)) lo = mid;
        else hi = mid;
    }
    return mp(min(lo,r),max(lo,r));
}

int _t, n;
cood xin, yin, a;
int main(){
    freopen("breakfree.in", "r", stdin);
    freopen("breakfree.out",  "w", stdout);
    scanf(" %d", &_t);
    while(_t--){
        cin >> a >> xin >> yin >> v;
        s = point(xin, yin);
        scanf(" %d", &n);
        for(int i=0;i<n;i++) {
            cin >> xin >> yin >> u[i];
            c[i] = point(xin, yin);
        }
        intervals = {{0,a}};
        for(int i=0;i<n;i++){
            aux.clear();
            for(auto I : intervals) {
                cood _x = x(intersect({I.fst,0},{I.snd,0},s,c[i]));
                //_x = x(proj({I.fst,0},{I.snd,0},c[i]));
                if(I.fst <= _x - eps && _x <= I.snd + eps) {
                    aux.pb(solve(I.fst,_x,i));
                    aux.pb(solve(_x,I.snd,i));
                } else aux.pb(solve(I.fst,I.snd,i));
            }
            intervals.clear();
            for(auto I : aux) if(fabs(I.snd - I.fst) > eps) intervals.pb(I);
        }
        cood ans = 0;
        for(auto I : intervals) ans += fabs(I.snd-I.fst);
        printf("%.20Lf\n", ans);
    }
}
