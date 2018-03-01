#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll k, d, t;
ll res;

int main () {
	scanf("%lld %lld %lld", &k, &d, &t);
	d = ((k+d-1)/d)*d;
	t += t;

	ll in = t/(k+d);
	res = in*d;
	t %= (k+d);
	
	if (t > k+k) res += t-(k+k);
	t = min(t,k+k);

	printf("%lld.%lld\n", res + t/2, (t%2)*5);
}
