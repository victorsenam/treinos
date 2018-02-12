#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6;

int n;

int main () {
	scanf("%d", &n);

	ll i;
	for (i = 2; n; i++) {
		bool ok = 1;
		for (ll j = 2; ok && j * j <= i; j++)
			if (i%j == 0)
				ok = 0;
		if (ok) n--;
	}

	printf("%lld\n", i-1);
}
