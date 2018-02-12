#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll a, b, c;

int main () {
	scanf("%lld %lld %lld", &a, &b, &c);

	if (a) {
		ll delta = b*b - 4ll*a*c;
		if (delta < 0) {
			printf("0\n");
		} else if (delta == 0) {
			printf("1\n");
			printf("%.20f\n", -.5*double(b)/double(a));
		} else {
			printf("2\n");
			double r = .5*(-b - sqrt(delta))/a;
			double s = .5*(-b + sqrt(delta))/a;
			if (r > s) swap(r,s);
			printf("%.20f\n%.20f\n",r,s);
		}
	} else if (b) {
		printf("1\n");
		printf("%.20f\n",-double(c)/double(b));
	} else if (c) {
		printf("0\n");
	} else {
		printf("-1\n");
	}
}
