#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;
ll l;
ll bst, c, res;
ll cur, i;
ll vl[31];

int main () {
	scanf("%d", &n);
	scanf("%lld", &l);

	ll aux = 0;
	bst = 1e9+2;
	res = LLONG_MAX;
	bool ok = 0;
	for (cur = 1, i = 0; i < 30; i++, cur += cur) {
		if (i < n)
			scanf("%lld", &c);
		else
			c = LLONG_MAX;
		bst += bst;
		bst = min(bst, c);
		aux = min(aux,bst);
		if (l & cur)
			aux += bst;
	}
	res = aux;

	printf("%lld\n", res);
}
