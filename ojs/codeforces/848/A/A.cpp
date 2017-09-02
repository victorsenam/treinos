#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll k;

ll go (ll i) {
	return i*(i-1)/2;
}

int main () {
	scanf("%lld", &k);
	if (k == 0)
		putchar('a');
	for (char a = 'a'; a <= 'z' && k; a++) {
		int i = 1;
		while (go(i+1) <= k)
			i++;
		k -= go(i);

		for (int j = 0; j < i; j++)
			putchar(a);
	}
	putchar('\n');
}
