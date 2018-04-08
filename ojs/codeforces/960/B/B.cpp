#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;

int n, k, kb;
int v[2][N];
int d[N];

int main () {
	scanf("%d %d %d", &n, &k, &kb);
	k += kb;

	for (int k = 0; k < 2; k++) for (int i = 0; i < n; i++)
		scanf("%d", &v[k][i]);

	for (int i = 0; i < n; i++) 
		d[i] = abs(v[0][i] - v[1][i]);

	sort(d, d+n);

	for (int i = n-1; i >= 0 && k; i--) {
		int sz = (n-i);
		int qt = (d[i] - d[i-1]);
		int x = min(k, sz*qt);
		k -= x;
		for (int j = 0; j < sz; j++) {
			int ch = (x+sz-1-j)/(sz-j);
			d[i+j] -= ch;
			x -= ch;
		}
	}

	if (k%2) d[0]++;
	ll res = 0;
	for (int i = 0; i < n; i++)
		res += ll(d[i])*d[i];
	printf("%lld\n", res);
}
