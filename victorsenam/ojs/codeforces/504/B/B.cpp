#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 200007;

int n;
int perm[3][N];

struct fen {
    int n;
    int v[N];

    void build (int s) {
        n = s;
        memset(v, 0, sizeof v);
    }
    
    void insert (int i, int x) {
        for (i+=2; i <= n+3; i+=(i&-i))
            v[i] += x;
    }

    int get (int i) {
        int res = 0;
        for (i+=2; i > 0; i-=(i&-i))
            res += v[i];
        return res;
    }
};

void convert (int k, int n) {
    fen bit;
    bit.build(n);

    for (int i = 0; i < n; i++) {
        int p = bit.get(perm[k][i]);
        bit.insert(perm[k][i], 1);
        perm[k][i] = (perm[k][i]-p);
    }
}

int getPos (fen & bit, int i) {
    int lo = 0; int hi = bit.n;

    while (lo < hi) {
        int mid = (hi+lo)/2;
        if (mid-bit.get(mid) >= i)
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

int main () {
    scanf("%d", &n);
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++)
            scanf("%d", &perm[k][i]);
        convert(k, n);
    }

    fen bit;
    bit.build(n);
    int car = 0;
    for (int i = 1; i <= n; i++) {
        perm[2][n-i] = car;
        for (int k = 0; k < 2; k++)
            perm[2][n-i] += perm[k][n-i];
        car = perm[2][n-i]/i;
        perm[2][n-i] %= i;
    }
    for (int i = 0; i < n; i++) {
        int p = getPos(bit, perm[2][i]);
        bit.insert(p, 1);
        printf("%d ", p);
    }
    printf("\n");
}
