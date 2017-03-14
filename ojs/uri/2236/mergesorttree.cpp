#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

//#define debug(...) {fprintf(stderr, __VA_ARGS__);}
#define debug(...) {}

const int N = 5e4+7;
const int K = 33;

int mrg[K][N];
int qrl, qrr;
int n, q;
int p[N];
int re[N];
int siz;

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

	}
}

int query (int k, int l, int r, int x) {
	if (qrl <= l && qrr >= r) {
		int loc = upper_bound(mrg[k]+l, mrg[k]+r, x) - mrg[k]-l;
		return loc;
	} else if (qrl >= r || qrr <= l)
		return 0;
	else
		return query(k+1, l, (l+r)/2, x) + query(k+1, (l+r)/2, r, x);
}

int get_best (int i, int j) {
    int a = query(0, 0, n, i);
    int b = query(0, 0, n, j);

    a = abs(a + a - siz);
    b = abs(b + b - siz);

    if (a < b || (a == b && i < j)) return i;
    return j;
}

int solve () {
    int res = 1;
    siz = qrr - qrl;

    int lo = 1;
    int hi = n;

    while (lo < hi) {
        int mid = (lo+hi)/2;
        int a = query(0, 0, n, mid);
        if (a + a <= siz)
            lo = mid + 1;
        else
            hi = mid;
    }

    debug("[%d]\n", lo);
    int sx = query(0, 0, n, lo-1);
    res = get_best(res, lo);


    lo = 1;
    hi = n;
    while (lo < hi) {
        int mid = (lo+hi)/2;
        int a = query(0, 0, n, mid);
        if (a >= sx)
            hi = mid;
        else
            lo = mid+1;
    }
    debug("[%d]\n", lo);

    res = get_best(res, lo);

	return res;
}

int dfs (int u) {
    if (re[u] != -1) return re[u];
    re[u] = u;
    return re[u] = dfs(p[u]);
}

int get_val (int u) {
    if (re[u] == u) return u;
    return min(u, get_val(p[u]));
}

int reach (int u) {
    if (re[u] == u) return mrg[K-1][u];
    re[u] = u;
    return mrg[K-1][u] = min(u, reach(p[u]));
}

int main () {
    memset(re, -1, sizeof re);
	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
        debug("%2d ", p[i]);
        p[i]--;
	}
    debug("\n");

    for (int i = 0; i < n; i++) {
        dfs(i);
        debug("%2d ", re[i]+1);
    }
    debug("\n");

    for (int i = 0; i < n; i++)
        if (re[i] == i)
            mrg[K-1][i] = get_val(p[i]);

    for (int i = 0; i < n; i++) {
        reach(i);
    }
    for (int i = 0; i < n; i++) {
        mrg[K-1][i]++;
        debug("%2d ", mrg[K-1][i]);
    }
    debug("\n");

	build(0, 0, n);
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &qrl, &qrr);
		qrl--;

		printf("%d\n", solve());
	}
}
