#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;
int k;

char p[N], t[N];
int n, m;
int zf[N], zb[N];

void Z (int n, char * s, int * z) {
	int m = -1;
	for (int i = 1; i < n; i++) {
		z[i] = 0;
		if (m != -1 && m + z[m] >= i)
			z[i] = min(m + z[m] - i, z[i-m]);
		while (i + z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
		if (m == -1 || i + z[i] > m + z[m])
			m = i;
	}
}

int main () {
	scanf(" %s %s %d", t, p, &k);
	m = strlen(t);
	n = strlen(p);

	for (int i = 0; t[i]; i++)
		p[n+i+1] = t[i];
	Z(n+m+1,p,zf);

	for (int i = 0; i < n/2; i++)
		swap(p[i], p[n-1-i]);
	for (int i = 0; i < m/2; i++)
		swap(p[i+n+1], p[n+m-i]);
	Z(n+m+1,p,zb);
	
	for (int i = 0; i < m/2; i++)
		swap(zb[i+n+1], zb[n+m-i]);

	vector<int> ans;
	for (int i = n+1; i+n <= n+m+1; i++){
		if (zf[i] + zb[i+n-1] + k >= n) ans.pb(i-n);
	}

	printf("%d\n", (int) ans.size());
	for (int x : ans)
		printf("%d ", x);
	printf("\n");
}
