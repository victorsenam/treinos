#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int n, a, b;
int p[N];

int main () {
	scanf("%d %d %d", &n, &a, &b);

	int k;
	for (k = 0; k*a <= n; k++) {
		if ((n - k*a)%b == 0) break;
	}

	if (k*a > n) {
		printf("-1\n");
		return 0;
	}

	for (int i = 0; i < n; i++) {
		p[i] = i;
	}

	int cur = 0;
	for (int i = 0; cur < n; i++) {
		int s = (i<k)?a:b;
		for (int j = cur; j < cur+s-1; j++)
			swap(p[j],p[j+1]);
		cur += s;
	}

	for (int i = 0; i < n; i++)
		printf("%d ", p[i]+1);
	printf("\n");
}
