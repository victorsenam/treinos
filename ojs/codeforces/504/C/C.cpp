#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

const int N = 112345;

int n;
int v[N];
int c[N];
int neg, imp;

int pref[N], mid[N];

inline void att (int x, int ch) {
    imp -= c[x]&1;
    neg -= c[x]<0;
    c[x] += ch;
    imp += c[x]&1;
    neg += c[x]<0;

    assert(imp >= 0);
    assert(neg >= 0);
}

inline void upd (int k, int ch, int i, int j) {
    bool isin = (i<=(n-k-1)&&j>=(n-k-1));
    att(v[k], ch);
    if (i == n/2 && (n&1))
        return;
    if (!isin) {
        att(v[n-k-1], -ch);
    } else {
        att(v[k], ch);
    }
}

bool ok (int i, int j) {
    DEBUG("[%d,%d] imp %d, neg %d || ", i, j, imp, neg);
    int mm = min(i, n-j);
    if (!pref[mm]) {
        DEBUG("prefix fail (%d)\n", mm);
        return 0;
    }
    mm = max((n+1)/2-j-1, i-n/2-1);
    if (mm >= 0 && !mid[mm]) {
        DEBUG("mid fail (%d)\n", mm);
        return 0;
    }

    int res = (imp <= 1 && neg == 0);
    DEBUG("is %d\n", res);
    return res;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    pref[0] = 1;
    mid[0] = 1;
    for (int i = 1; i <= n; i++) {
        pref[i] = (pref[i-1]&&(v[i-1]==v[n-i]));
        printf("%d ", pref[i]);
    }
    printf("\n");
    for (int i = 1; i <= (n+1)/2; i++) {
        mid[i] = (mid[i-1]&&(v[(n)/2-i+1]==v[n/2+i-1]));
        printf("%d ", mid[i]);
    }
    printf("\n");

    int j = 0;
    ll res = 0;
    upd(j, 1, 0, 0);

    for (int i = 0; i < n; i++) {
        while (i > j || (j < n && !ok(i, j))) {
            upd(j, 1, i, j);
            j++; 
        }

        if (j < n) {
            DEBUG("ok [%d,%d]\n", i, j);
            res += (n-j);
        }
        upd(i, -1, i+1, j);
    }

    printf("%lld\n", res);
}
