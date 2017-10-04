#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6;

int n;
int p[N];
int c[N];

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		p[i] = i;
	int bst = 0;

	do {
		int cur = 0;
		for (int i = 0; i < n-1; i++)
			cur += abs(p[i] - p[i+1]);
		if (cur > bst) {
			bst = cur;
			for (int i = 0; i < n; i++)
				c[i] = p[i];
		}
	} while (next_permutation(p, p+n));

	printf("%d\n", bst);
	for (int i = 0; i < n; i++)
		printf("%d ", c[i]);
	printf("\n");
}
