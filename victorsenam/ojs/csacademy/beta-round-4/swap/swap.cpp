#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

int n;
int bit[N];
int v[N];
int p[N];

void insert (int p, int x) {
    p++;
    for (int i = p; i <= n; i+= (i&-i))
        bit[i] += x;
}

int get (int p) {
    p++;
    int val = 0;
    for (int i = p; i > 0; i-= (i&-i))
        val += bit[i];
    return val;
}

bool cmp_t (int i, int j) {
    if (v[i] == v[j]) return i < j;
    return v[i] < v[j];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);
        p[i] = i;
    }
    sort(p, p+n, cmp_t);
    for (int i = 0; i < n; i++)
        printf("%d ", v[p[i]]);
    printf("\n");

    int res = 0;

    for (int i = 0; i < n; i++) {
        p[n] = v[i];
        int ps = lower_bound(p, p+n, n, cmp_t) - p;
        printf("[ %d: %d\n", v[i], p[ps]);

        res += p[ps] - p[ps+1] - get(p[ps+1]) + get(p[ps]);
        printf("%d: %d\n", v[i], p[ps] - p[ps+1] - get(p[ps+1]) + get(p[ps]));
        insert(p[ps+1], 1);
    }
    printf("%d\n", res);
}
