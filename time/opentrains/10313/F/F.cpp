#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;
typedef long double cood;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const ll N = 1e5;

int n;
cood x[3], tot;
ll a[3];

ll read () {
	ll a;
	scanf("%lld", &a);
}

int main () {
	scanf(" %d", &n);
	while(n--){
		cin >> x[0] >> x[1] >> x[2];

		for (int i = 0; i < 3; i++) {
			a[i] = x[i] * N + .5;
		}

		ll prod = 1ll;
		ll sum = 0ll;

		for (int i = 0; i < 3; i++) {
			prod *= a[i];
		}

		for (int i = 0; i < 3; i++) {
			ll loc = N;
			for (int j = 0; j < 3; j++)
				if (i != j)
					loc *= a[j];
			sum += loc;
		}
		
		if(sum < prod) puts("YES");
		else              puts("NO");
	}
}
