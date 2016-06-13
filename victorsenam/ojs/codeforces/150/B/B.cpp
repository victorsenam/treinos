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

const ll MOD = 1000000007ll;

const int N = 2007;

int uf[N], wf[N];
int n, k;
ll m, res;

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ( (i = find(i)) == (j = find(j)) ) return;
    if (wf[i] < wf[j]) swap(i, j);
    uf[j] = i;
    wf[i] += wf[j];
}


int main () {
    scanf("%d " LLD " %d", &n, &m, &k);

    res = 1;
    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++)
            if (i - j >= 0 && i - j + k - 1 < n)
                join(i, i+k-j-j-1);
    }

    for (int i = 0; i < n; i++)
        if (i == find(i))
            res = (res*m)%MOD;

    printf(LLD "\n", res);
}
