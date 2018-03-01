#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e5+7;

int n, q;
int sq;
ll v[N];
int l[N], r[N];
int qr[N];
int p[N], q[N];
int rr[N][3];

void rem (int i) {
	if (pr[i] >= 0) pr[i] = pr[pr[i]];
	if (nx[i] < n) nx[i] = nx[nx[i]];
}

int main () {
	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++) {
		scanf("%lld", &v[i]);
		p[i] = i;
	}
	sort(p, p+n, [] (int i, int j) { return v[i] < v[j]; });
	for (int i = 0; i < n; i++)
		q[p[i]] = i;

	sq = sqrt(n);
	for (int i = 0; i < q; i++) {
		scanf("%lld %lld", &l[i], &r[i]);
		qr[i] = i;
	}

	sort(qr, qr+q, [] (int i, int j) { return (l[i]/sq)!=(l[j]/sq)?(l[i]/sq)<(l[j]/sq):r[i]<r[j]; });

	int qs = 0;
	for (int i = 0; i < n; i += sq) {
		for (int j = 0; j < n; j++) {
			pr[j] = q[p[j]-1];
			nx[j] = q[p[j]+1];
		}
		for (int j = 0; j < i; j++)
			rem(j);
	}
	
	for (int i = 0; i < q; i++) {
		if (rr[i][0] == -1) printf("-1\n");
		else printf("%d %d %d\n", rr[i][0], rr[i][1], rr[i][2]);
	}
}
