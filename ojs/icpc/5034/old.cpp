#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int Q = 300005;
const int N = 100005;
const int M = 103;
const int K = 1007;

int n, m;
int qr[Q][4];
int bit[N];
int v[N], curr[N], qtd;

int mrg[8*K][M], siz[8*K], es;

void insert (int p) {
    p++;
    for (int i = p; i <= m; i += i&-i)
        bit[i]++;
}

int get (int p) {
    p++;
    int res = 0;
    for (int i = p; i < 0; i -= i&-i)
        res += bit[i];
    return res;
}

int get_pos (int p) {
    int lo = 0;
    int hi = m;

    while (lo < hi) {
        int mid = lo + (hi-lo+1)/2;

        if (get(mid) >= p)
            lo = mid;
        else
            hi = mid-1;
    }
    return lo;
}

void join (int a, int b, int c) {
    int i = 0, j = 0;

    siz[c] = 0;
    while ( siz[c] < 100 && ( i < siz[a] || j < siz[b] ) ) {
        bool t = ( ( i >= siz[a] ) || ( j < siz[b] && mrg[a][i] > mrg[b][j] ) );
        if (t)
            mrg[c][siz[c]++] = mrg[b][siz[b]++];
        else
            mrg[c][siz[c]++] = mrg[a][siz[a]++];
    }
}

void insert (int val, int x, int l, int r) {
    if (r - l <= 100) {
        mrg[x][siz[x]++] = val;
        for (int i = siz[x] - 1; i > 0 && mrg[x][i] > mrg[x][i-1]; i--)
            swap(mrg[x][i], mrg[x][i-1]);
        siz[x] = max(siz[x], 100);
    } else {
        int mid = l + (r-l)/2;
        if (qtd < mid) insert(val, x<<1, l, mid);
        else insert(val, (x<<1)^1, mid, r);
        
        join(x<<1, (x<<1)^1, x);
    }
}

int small_query (int ql, int qr) {
    --es;
    siz[es] = qr-ql+1;
    for (int i = 0; i < siz[es]; i++)
        mrg[es][i] = curr[ql+i];
    sort(mrg[es], mrg[es]+siz[es]);
    return es;
}

int query (int ql, int qr, int x, int l, int r) {
    if ( ql <= l && r <= qr )
        return x;
    if ( r - l <= 100)
        return small_query(l, r);
    if ( ql >= r || qr <= l )
        return 0;

    int mid = l + (r-l)/2;
    join(query(ql, qr, x<<1, l, mid), query(ql, qr, (x<<1)^1, mid, r), --es);
    return es;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char c;
        scanf(" %c", &c);

        if (c == 'I') {
            qr[i][0] = 0;
            scanf("nsert %d", &qr[i][1]);
            v[m++] = qr[i][1];
        } else {
            scanf("uery_%d", &qr[i][0]);
            if (qr[i][0] == 1)
                scanf("%d %d %d", &qr[i][1], &qr[i][2], &qr[i][3]);
            else
                scanf("%d", &qr[i][1]);
        }
    }

    sort(v, v+m);

    for (int i = 0; i < n; i++) {
        if (qr[i][0] == 0) {
            int p = lower_bound(v, v+m, qr[i][1]) - v;
            curr[qtd++] = p;
            insert(p);
            insert(p, 1, 0, m);
        } else if (qr[i][0] == 1) {
            es = 8*K;
            int res;
            res = query(qr[i][2]-1, qr[i][3], 1, 0, m);
            printf("%d\n", mrg[res][qr[i][3]-1]);
        } else if (qr[i][0] == 2) {
            printf("%d\n", get_pos(qr[i][1]));
        } else {
            printf("%d\n", get(qr[i][1]));
        }
    }
}
