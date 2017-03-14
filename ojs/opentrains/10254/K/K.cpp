#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5 + 7;

ll v[N];
int p[N];
int n, k;
ll q;

bool cmp_t (int i, int j) {
    return v[i] < v[j];
}

int main () {
    scanf("%d %d", &n, &k);

    v[0] = p[0] = 0;
    for (int i = 1; i < n; i++) {
        scanf("%lld", &q);
        v[i] = v[i-1] + q;
        p[i] = i;
    }

    sort(p, p+n, cmp_t);
    int mini = 0;
    for (int i = 1; i + k - 1 < n; i++) {
        if (abs(v[p[i+k-1]] - v[p[i]]) < abs(v[p[mini+k-1]] - v[p[mini]]))
            mini = i;
    }

    printf("%lld\n", abs(v[p[mini+k-1]] - v[p[mini]]));
    for (int i = 0; i < k; i++)
        printf("%d ", p[i+mini]+1);
    printf("\n");
}
