#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 3e4+7;
const int K = 30;
int n, q;

int ql, qr, qk;
int mrg[K][N];

void build (int k, int l, int r) {
	if (l + 1 == r)
		mrg[k][l] = mrg[K-1][l];
	else {
		int mid = (l+r)/2;
		build(k+1, l, mid);
		build(k+1, mid, r);

		int p[2] = {l, mid};
		int ps = l;

		while (p[0] < mid || p[1] < r) {
			bool b = (p[0] >= mid || (p[1] < r && mrg[k+1][p[0]] > mrg[k+1][p[1]]));
			mrg[k][ps++] = mrg[k+1][p[b]++];
		}
	}
}

int get (int k, int l, int r) {
	if (l >= ql && r <= qr) {
		return upper_bound(mrg[k]+l, mrg[k]+r, qk) - mrg[k] - l;
	} else if (r <= ql || l >= qr) {
		return 0;
	} else {
		return get(k+1, l, (l+r)/2) + get(k+1, (l+r)/2, r);
	}
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &mrg[K-1][i]);

	build(0, 0, n);

	int qs;
	scanf("%d", &qs);
	int ls = 0;
	while (qs--) {
		scanf("%d %d %d", &ql, &qr, &qk);
		ql ^= ls;
		qr ^= ls;
		qk ^= ls;
		ql--;
		ql = max(ql, 0);
		qr = min(qr, n);
		if (ql >= qr) {
			ls = 0;
		} else {
			ls = qr - ql - get(0, 0, n);
		}
		printf("%d\n", ls);
	}
}
