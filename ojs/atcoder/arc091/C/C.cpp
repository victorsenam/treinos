#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, m;

int main () {
	scanf("%lld %lld", &n, &m);

	if (n == 1) {
		if (m == 1) printf("1\n");
		else printf("%lld\n", m-2);
	} else {
		if (m == 1) printf("%lld\n", n-2);
		else printf("%lld\n", (n-2)*(m-2));
	}
}
