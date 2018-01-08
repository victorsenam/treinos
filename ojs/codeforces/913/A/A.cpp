#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, m;

int main () {
	scanf("%lld %lld", &m, &n);

	if (m > 40) printf("%lld\n", n);
	else printf("%lld\n", n%(1ll<<m));
}
