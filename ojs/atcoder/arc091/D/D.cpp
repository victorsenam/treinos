#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, k;

int main () {
	scanf("%lld %lld", &n, &k);

	ll res = 0;
	for (ll b = k+1; b <= n; b++) {
		ll loc = (n/b)*(b-k);
		if (n%b >= k) loc += (n%b) - k + 1;
		if (k == 0) loc--;
		res += loc;
	}

	printf("%lld\n", res);
}
