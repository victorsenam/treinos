#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

ll a, b;
int sie[N];

int main () {
	scanf("%lld %lld", &a, &b);

	for (ll i = 1; i < N; i++)
		for (ll j = i; j < N; j += i)
			sie[j]++;
	int res = 0;
	for (int i = a; i <= b; i++)
		res += (sie[i]&1);
	printf("%d\n", res);
}
