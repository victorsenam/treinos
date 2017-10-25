#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, k;

int main () {
	scanf("%d %d", &n, &k);

	if ((n == 2 || n == 3) && k == 0) {
		printf("-1\n");
		return 0;
	} else if (n > 3 && k == 0) {
		printf("%d\n", 6 + (n-4)*2);
		printf("1 2 2\n2 3 2\n1 4 2\n2 4 1\n1 3 1\n3 4 1\n");
		for (int i = 5; i <= n; i++)
			printf("%d 1 1\n%d 2 2\n", i, i);
		return 0;
	}

	printf("%d\n", k + (n-k-1)*2);
	for (int i = 1; i <= k; i++)
		printf("%d %d 2\n", i, i+1);

	for (int i = k+2; i <= n; i++) {
		printf("%d %d 1\n", i, 1);
		printf("%d %d 3\n", i, k+1);
	}
}
