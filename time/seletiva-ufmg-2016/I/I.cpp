#include <bits/stdc++.h>
using namespace std;
typedef double cood;
typedef complex<cood> point;
const cood PI = acos(-1.0);
const cood eps = 1e-9;

cood inner(point a, point b)
{ return real(conj(a)*b); }

cood xin, yin;
point a, b, s, p[2], ans;

int main(){
	scanf(" %lf%lf", &xin, &yin); a = point(xin, yin);
	scanf(" %lf%lf", &xin, &yin); b = point(xin, yin);
	scanf(" %lf%lf", &xin, &yin); s = point(xin, yin);

	if(abs(a-b) < eps){
		printf("%.2lf %.2lf\n", xin, yin);
		return 0;
	}

	p[0] = .5*(a+b);
	p[1] = p[0] + (a-b)*polar(1./abs(a-b), .5*PI);
	ans = p[0] + (p[1]-p[0])*inner(s-p[0],p[1]-p[0]);

	printf("%.2lf %.2lf\n", real(ans), imag(ans));
}
