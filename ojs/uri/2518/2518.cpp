#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;
double h,c,l;

int main () {
	while (	scanf("%d %lf %lf %lf", &n, &h, &c, &l) != EOF) {
		h /= 100; c /= 100; l /= 100;
		printf("%.4f\n", sqrt(c*c + h*h)*l*n);
	}
}
