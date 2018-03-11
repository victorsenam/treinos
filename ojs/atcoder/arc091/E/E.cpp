#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e5+7;

ll n, a, b;
int v[N];

int main () {
	scanf("%lld %lld %lld", &n, &a, &b);

	if (n < a + b - 1 || n > a*b) { printf("-1\n"); return 0; }

	bool s = 0;
	if (a < b) { swap(a,b); s = 1; }
	
	int dec = n - a;

	ll p = 0;
	for (ll i = 1; i <= n;) {
		ll s = p;
		for (ll j = 0; j < b && p < n; j++, p++) {
			if (j && !dec) break;
			v[p] = j + i;
			if (j) dec--;
		}
		i = v[p-1] + 1;
		reverse(v+s,v+p);
	}

	for (int i = 0; i < n; i++) printf("%lld ", s?n-v[i]+1:v[i]);
	printf("\n");
}
