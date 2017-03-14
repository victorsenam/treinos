#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

int n;
map<ull, ull> mp;
ull a;
char c;

ull conv (ll a) {
	ll e = 1;
	ll r = 0;
	while (a) {
		r += (a&1)*e;
		a /= 10;
		e <<= 1;
	}
	return r;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf(" %c %llu", &c, &a);

		if (c == '?') {
			printf("%llu\n", mp[conv(a)]);
		} else if (c == '+') {
			mp[conv(a)]++;
		} else {
			mp[conv(a)]--;
		}
	}

}
