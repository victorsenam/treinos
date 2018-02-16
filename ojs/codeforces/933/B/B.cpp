#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 200;

ll p, k;
ll r[N];

int main () {
	scanf("%lld %lld", &p, &k);

	int i;
	for (i = 0; p; i++) {
		if (p > 0) {
			r[i] = p%k;
			p = -(p/k);
		} else {
			r[i] = ((k + (p%k)))%k;
			p = (-p+k-1)/k;
		}
	}

	printf("%d\n", i);
	for (int j = 0; j < i; j++)
		printf("%lld ", r[j]);
	printf("\n");
}
