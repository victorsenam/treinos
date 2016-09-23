#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 5e4+7;
const int K = 33;

int mrg[K][N];
int qrl, qrr;
int n, q;
int p[N];

void build (int k, int l, int r) {
	if (l + 1 == r) {
		mrg[k][l] = mrg[K-1][l];
	} else { 
		int mid = (l+r)/2;
		int q[2] = {l, mid};
		build(k+1, l, q[1]);
		build(k+1, q[1], r);
		int ps = l;

		while (q[0] < mid || q[1] < r) {
			bool cr = ((q[0] == mid) || (q[1] < r && mrg[k+1][q[1]] < mrg[k+1][q[0]]));
			mrg[k][ps++] = mrg[k+1][q[cr]++];
		}

		debug("%d[%d,%d):", k, l, r);
		for (int i = l; i < r; i++)
			debug(" %d", mrg[k][i]);
		debug("\n");
	}
}

int query (int k, int l, int r, int x) {
	if (qrl <= l && qrr >= r)
		return upper_bound(mrg[k]+l, mrg[k]+r, x) - mrg[k]-l;
	else if (qrl >= r || qrr <= l)
		return 0;
	else
		return query(k+1, l, (l+r)/2, x) + query(k+1, (l+r)/2, r, x);
}

int solve () {
	int lo = 0;
	int hi = n;
	int siz = qrr - qrl;

	while (lo < hi) {
		int mid = (lo + hi)/2;
		int loc = query(0, 0, n, mid);

		if (loc + loc >= siz)
			hi = mid;
		else
			lo = mid + 1;
	}

	if (lo == 0) return lo;

	int aval = query(0, 0, n, lo);
	int bval = query(0, 0, n, lo-1);

	if (abs(aval + aval - siz) > abs(bval + bval - siz)) return lo;

	lo = 0;
	hi = n;
	
	while (lo < hi) {
		int mid = (lo + hi)/2;
		int loc = query(0, 0, n, mid);
		
		if (loc >= bval)
			hi = mid;
		else
			lo = mid + 1;
	}

	return lo;
}

int main () {
	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
		mrg[K-1][i] = p[i];
	}

	build(0, 0, n);
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &qrl, &qrr);
		qrl--;

		printf("%d\n", solve());

	}
}
