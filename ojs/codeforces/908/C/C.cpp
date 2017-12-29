#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
int n;
ll r;
ll x[N];
double y[N];


int main () {
	scanf("%d %lld", &n, &r);

	for (int i = 0; i < n; i++) {
		scanf("%lld", &x[i]);

		y[i] = r;
		for (int j = 0; j < i; j++) {
			ll d = abs(x[i] - x[j]);
			if (d > r+r) continue;
			y[i] = max(y[i], y[j] + sqrt(4*r*r - d*d));
		}

		printf("%.20f ", y[i]);
	}
}
