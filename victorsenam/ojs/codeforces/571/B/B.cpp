#include <bits/stdc++.h>

using namespace std;

const int K = 5007;
const int N = 300007;

typedef long long int num;

num memo[K][K];
int n, k;
num a[N];
num res;

num pd (int c, int f) {
    if (c + f == k-1)
        return 0;

    num & m = memo[c][f];
    int i = c*((n+k-1)/k) + f*(n/k);

    if (m != -1)
        return m;

    m = 0;
    if (c < n%k)
        m = max(m, a[i+(n+k-1)/k]-a[i+(n+k-1)/k-1] + pd(c+1, f));
    if (f < k-(n%k))
        m = max(m, a[i+n/k]-a[i+n/k-1] + pd(c, f+1));

    return m;
}

int main () {
    scanf("%d %d", &n, &k);
    memset(memo, -1, sizeof memo);

    for (int i = 0; i < n; i++)
        scanf("%I64d", a+i);

    sort(a, a+n);
    for (int i = 1; i < n; i++)
        res += a[i] - a[i-1];

    if (k >= n)
        printf("%I64d\n", res);
    else
        printf("%I64d\n", res-pd(0,0));
}
