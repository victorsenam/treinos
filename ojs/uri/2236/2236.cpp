#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

//#define debug(...) {fprintf(stderr, __VA_ARGS__);}
#define debug(...) {}

const int N = 5e4+7;
const int K = 33;
const int S = N*K;

int lf[S], rf[S], ch[S][2];
int es;
int val[S];

int qrl, qrr;
int n, q;
int p[N];
int re[N];
int siz;

int rt[N];
int cv[N];
int sr[N];

int build (int l, int r) {
    lf[es] = l;
    rf[es] = r;
    val[es] = 0;
    ch[es][0] = 0;
    ch[es][1] = 0;
    int o = es++;

    if (l + 1 != r) {
        ch[o][0] = build(l, (r+l)/2);
        ch[o][1] = build((r+l)/2, r);
    }
    //debug("%d[%d,%d) : %d -> [%d|%d]\n", o, lf[o], rf[o], val[o], ch[o][0], ch[o][1]);
    return o;
}

int add (int o, int x, int i) {
    if (i < lf[o] || rf[o] <= i) return o;
    
    lf[es] = lf[o];
    rf[es] = rf[o];
    val[es] = val[o];
    ch[es][0] = ch[o][0];
    ch[es][1] = ch[o][1];
    o = es++;

    if (lf[o] == i && rf[o] == i+1) {
        val[o]++;
    } else {
        val[o] = 0;
        for (int k = 0; k < 2; k++) {
            ch[o][k] = add(ch[o][k], x, i); 
            val[o] += val[ch[o][k]];
        }
    }

    //debug("%d[%d,%d) : %d -> [%d|%d]\n", o, lf[o], rf[o], val[o], ch[o][0], ch[o][1]);
    return o;
}

int query (int o) {
    if (qrr <= lf[o] || qrl >= rf[o]) return 0;
    if (qrl <= lf[o] && qrr >= rf[o]) return val[o];
    return query(ch[o][0]) + query(ch[o][1]);
}

int get_best (int i, int j) {
    int a = query(rt[i]);
    int b = query(rt[j]);

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
        int a = query(rt[mid]);
        debug("%d leq %d in %d[%d,%d)\n", a, mid, rt[mid], qrl, qrr+1);
        if (a + a <= siz)
            lo = mid + 1;
        else
            hi = mid;
    }

    debug("[%d]\n", lo);
    int sx = query(rt[lo-1]);
    res = get_best(res, lo);


    lo = 1;
    hi = n;
    while (lo < hi) {
        int mid = (lo+hi)/2;
        int a = query(rt[mid]);
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
    if (re[u] == u) return cv[u];
    re[u] = u;
    return cv[u] = min(u, reach(p[u]));
}

bool cmp_t (int i, int j){
    return cv[i] < cv[j];
}

int main () {
    es = 2;
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
            cv[i] = get_val(p[i]);

    for (int i = 0; i < n; i++) {
        reach(i);
    }
    for (int i = 0; i < n; i++) {
        cv[i]++;
        debug("%2d ", cv[i]);
        sr[i] = i;
    }
    debug("\n");

    sort(sr, sr+n, cmp_t);

	rt[0] = build(0, n);
    int l = 0;
    for (int i = 1; i <= n; i++) {
        rt[i] = rt[i-1];
        while (l < n && cv[sr[l]] <= i) {
            //debug("add %d (of val %d)\n", sr[l], cv[sr[l]]);
            rt[i] = add(rt[i], 1, sr[l]);
            l++;
        }
        debug("================================ last %d : %d\n", i, rt[i]);
    }
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &qrl, &qrr);
		qrl--;

		printf("%d\n", solve());
	}
}
