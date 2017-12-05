#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 23;

int n;
int a[N], v[N];
int p[N], q[N];

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		p[i] = i;
	}

	sort(p, p+n, [] (int i, int j) {
		return a[i] < a[j];
	});

	for (int i = 0; i < n; i++) {
		q[p[i]] = i;
	}
	
	for (int i = 0; i < n; i++) {
		if (q[i] != n-1)
			v[i] = a[p[q[i]+1]];
		else
			v[i] = a[p[0]];
	}

/*
	for (int mask = 1; mask < (1<<n) - 1; mask++) {
		int s = 0;
		for (int i = 0; i < n; i++) {
			if (mask&(1<<i))
				s += v[i] - a[i];
		}

		assert(s);
	}
*/

	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}
