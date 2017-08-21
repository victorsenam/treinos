#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int n;
ll a[N];
map<ll,ll> fr;

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
		fr[-a[i]]++;
	}

	ll fs = 0;
	for (auto it : fr) {
		if (fs == 0 && it.second >= 4) {
			printf("%lld\n", it.first*it.first);
			return 0;
		} else if (it.second >= 2) {
			if (fs == 0)
				fs = it.first;
			else {
				printf("%lld\n", fs*it.first);
				return 0;
			}
		}
	}

	printf("0\n");
}
