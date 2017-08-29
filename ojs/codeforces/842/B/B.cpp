#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll r, d;
int n;
ll x, y, s;

int main () {
	scanf("%lld %lld %d", &r, &d, &n);

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &x, &y, &s);

		if (x*x + y*y >= (r - d + s)*(r - d + s) && x*x + y*y <= (r - s)*(r - s)) {
			cnt++;
			//printf("%d\n", i+1);
		}

	}
	printf("%d\n", cnt);
}
