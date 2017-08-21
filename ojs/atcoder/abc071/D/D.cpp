#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll MOD = 1e9+7;

inline ll mod (ll x) {
	return x%MOD;
}

char str[2][100];
int n;

int main () {
	scanf("%d", &n);
	scanf(" %s %s", str[0], str[1]);

	ll r = 1;

	int ls = 1;

	for (int i = 0; i < n; i++) {
		if (str[0][i] == str[1][i]) {
			if (!i)
				r = 3;
			else if (ls == 1)
				r = mod(r+r);
			
			ls = 1;
		} else {
			if (!i)
				r = 6;
			else if (ls == 1)
				r = mod(r+r);
			else
				r = mod(r+r+r);
			i++;

			ls = 2;
		}
	}

	printf("%lld\n", r);
}
