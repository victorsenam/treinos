#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int Q = 300007;
const int N = 100007;
const int K = 104;

int qs, n;
int sz;
int v[N];
int ord[N];
int qr[Q][4];
ll res[4];

struct fen {
    int bit[N];

    void reset () {
        memset(bit, 0, sizeof bit);
    }
    
    void insert (int p, int x) {
        p++;
        for (int i = p; i <= n; i += i&-i)
            bit[i] += x;
    }

    int get (int p) {
        p++;
        int val = 0;
        for (int i = p; i > 0; i -= i&-i)
            val += bit[i];
        return val;
    }

    int select (int k) {
        int lo = 0;
        int hi = n-1;
        
        while (lo < hi) {
            int mid = (lo+hi)/2;
            if (get(mid) >= k)
                hi = mid;
            else
                lo = mid+1;
        }
        return lo;
    }
};

struct seg {
    int ql, qr, es;
    int l[8*N], r[8*N], mrg[8*N][K], siz[8*N];

    void build (int x, int ql, int qr) {
        l[x] = ql; r[x] = qr; siz[x] = 0;
        if (ql + 1 >= qr)
            return;
        int mid = ql + (qr-ql)/2;
        build(x<<1, ql, mid);
        build((x<<1)^1, mid, qr);
    }

    void debug (int x) {
        printf("[%d,%d):", l[x], r[x]);
        for (int i = 0; i < siz[x]; i++)
            printf(" %d", mrg[x][i]);
        printf("\n");
    }

    void debug_rec (int x) {
        if (l[x] >= r[x]) return;
        printf("[%d,%d):", l[x], r[x]);
        for (int i = 0; i < siz[x]; i++)
            printf(" %d", mrg[x][i]);
        printf("\n");
        debug_rec(x<<1);
        debug_rec((x<<1)^1);
    }

    int insert (int x, int val) {
        if (sz < l[x] || sz >= r[x]) return x;

        mrg[x][siz[x]++] = val;
        for (int tp = siz[x]-1; tp > 0 && mrg[x][tp] < mrg[x][tp-1]; tp--)
            swap(mrg[x][tp], mrg[x][tp-1]);
        siz[x] = min(siz[x], K-1);

        if (l[x] + 1 < r[x]) {
            insert(x<<1, val);
            insert((x<<1)^1, val);
        }
        return x;
    }

    int join (int a, int b) {
        if (!a) return b;
        if (!b) return a;
        int c = --es;

        int i = 0, j = 0;
        l[c] = l[a]; r[c] = r[b]; siz[c] = 0;
 //       DEBUG("join %d[%d,%d) %d[%d,%d) -> %d[%d,%d)\n", a, l[a], r[a], b, l[b], r[b], c, l[c], r[c]);
        while ( siz[c] < 100 && i < siz[a] && j < siz[b] ) {
            if ( mrg[a][i] < mrg[b][j] )
                mrg[c][siz[c]++] = mrg[a][i++];
            else
                mrg[c][siz[c]++] = mrg[b][j++];
        }
        while ( siz[c] < 100 && i < siz[a] )
            mrg[c][siz[c]++] = mrg[a][i++];
        while ( siz[c] < 100 && j < siz[b] )
            mrg[c][siz[c]++] = mrg[b][j++];
        return c;
    }

    int get (int x) {
        if (ql >= r[x] || qr <= l[x]) {
       //     DEBUG("get [%d,%d) %d[%d,%d) -> 0\n", ql, qr, x, l[x], r[x]);
            return 0;
        }
        if (ql <= l[x] && qr >= r[x]) {
     //       DEBUG("get [%d,%d) %d[%d,%d) -> full\n", ql, qr, x, l[x], r[x]);
            return x;
        }
        
        int ret = join(get(x<<1), get((x<<1)^1));
   //     DEBUG("get [%d,%d) %d[%d,%d) -> %d[%d,%d)\n", ql, qr, x, l[x], r[x], ret, l[ret], r[ret]);
        return ret;
    }

    int get (int l, int r) {
        ql = l;
        qr = r;
        es = 8*N;
        return get(1);
    }
};

fen bit;
seg tree;

int main () {
    int ts = 0;
    while (scanf("%d", &qs) != EOF) {
        printf("Case %d:\n", ++ts);
        n = 0;
        for (int i = 0; i < qs; i++) {
            char c;
            scanf(" %c", &c);

            if (c == 'I') {
                qr[i][0] = 0;
                scanf("nsert %d", &v[n++]);
                qr[i][1] = v[n-1];
                ord[n-1] = v[n-1];
            } else {
                scanf("uery_%d", &qr[i][0]);

                if (qr[i][0] == 1) {
                    scanf("%d %d %d", &qr[i][1], &qr[i][2], &qr[i][3]);
                } else {
                    scanf("%d", &qr[i][1]);
                }
            }
        }

        sort(ord, ord+n);

        sz = 0;
        for (int i = 0; i < 4; i++)
            res[i] = 0;
        bit.reset();
        tree.build(1, 0, n);

        for (int i = 0; i < qs; i++) {
            if (qr[i][0] == 0) {
                int ps = lower_bound(ord, ord+n, qr[i][1]) - ord;
                bit.insert(ps, 1);
                tree.insert(1, qr[i][1]);
                sz++;
  //              tree.debug_rec(1);
            } else if (qr[i][0] == 1) {
                int vert = tree.get(qr[i][1]-1, qr[i][2]);
                DEBUG("%d-th element on %d[%d,%d) : ", qr[i][3], vert, qr[i][1]-1, qr[i][2]);
                DEBUG("%d\n", tree.mrg[vert][qr[i][3]-1]);
 //               tree.debug(vert);
                res[1] += tree.mrg[vert][qr[i][3]-1];
            } else if (qr[i][0] == 2) {
                int ps = lower_bound(ord, ord+n, qr[i][1]) - ord;
                res[2] += bit.get(ps);
                DEBUG("%d's rank : %d\n", qr[i][1], bit.get(ps));
            } else {
                DEBUG("%d-th element : %d\n", qr[i][1], ord[bit.select(qr[i][1])]);
                res[3] += ord[bit.select(qr[i][1])];
            }
        }

        for (int i = 1; i <= 3; i++)
            printf("%lld\n", res[i]);
    }
}
