
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;
int n;
int a[N];
ll res = 0;

int main () {
	scanf("%d", &n);


	int ls = -1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);

		if (a[i] == 0)
			ls = i;

		res += i - ls;
	}

	printf("%lld\n", res);
}
