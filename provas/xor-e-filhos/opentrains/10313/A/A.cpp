#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;
typedef double cood;
typedef complex<cood> point;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5;

int n, m;
double xin, yin;
point P[N], a, b;
cood inner(point a, point b) { return real(conj(a)*b); }
cood cross(point a, point b) { return imag(conj(a)*b); }
point proj(point a, point b, point c)
{ return a + (inner(b-a,c-a)/norm(b-a))*(b-a);}
point reflect(point a, point b, point c)
{ return c + cood(2)*(proj(a,b,c)-c);}

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf(" %d%d", &n, &m);
	for(int i=0;i<n;i++){
		scanf(" %lf%lf", &xin, &yin);
		P[i] = {xin, yin};
	}
	for(int i=0;i<m;i++){
		scanf(" %lf%lf", &xin, &yin); a = {xin, yin};
		scanf(" %lf%lf", &xin, &yin); b = {xin, yin};
		for(int i=0;i<n;i++)
			if(cross(b-a,P[i]-a) < 0.) P[i] = reflect(a,b,P[i]);
	}
	for(int i=0;i<n;i++) printf("%lf %lf\n", real(P[i]), imag(P[i]));
}
