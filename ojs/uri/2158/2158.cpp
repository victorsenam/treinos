#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll a, b;

int main () {
	int tt = 1;
	while (scanf("%lld %lld", &a, &b) != EOF) {
		ll e = (a*5ll + b*6ll)/2;
		ll v = 2 + e - a - b;
		printf("Molecula #%d.:.\nPossui %lld atomos e %lld ligacoes\n", tt++, v, e);
		if (tt > 1) putchar('\n');
	}
}
