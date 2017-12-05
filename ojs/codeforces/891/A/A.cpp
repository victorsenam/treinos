#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3+7;

ll a[N];
int n;

int main () {
	ll ls = 1;
	int r = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
	}

	for (int i = 0; i < 1; i++) {
		ll c = a[i];
		if (c == 1)
			break;
		int j = i+1;
		for (j = i+1; j < n && c != 1; j++) {
			c = __gcd(c,a[j]);
		}
		
		if (c != 1) {
			printf("-1\n");
			return 0;
		}

		r = j - 1;
		for (j = j-1; j > i; j--) {
			a[j-1] = __gcd(a[j],a[j-1]);
		}
	}
	for (int i = 1; i < n; i++) {
		if (a[i] != 1)
			r++;
	}

	printf("%d\n", r);
}
