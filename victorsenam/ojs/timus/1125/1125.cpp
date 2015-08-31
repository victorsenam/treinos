#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 47;
const int K = 5;

num memo[N][K];
int n;

num pd (int i, int cor) {
    if (i == n)
        return cor;

    if (memo[i][cor] != -1)
        return memo[i][cor];

    if (cor) {
        memo[i][cor] = pd(i+1, 1) + pd(i+1, 0);
    } else {
        memo[i][cor] = pd(i+1, 1);
    }
    return memo[i][cor];
}

int main () {
    scanf("%d", &n);
    memset(memo, -1, sizeof(memo));

    printf("%lld\n", 2*pd(1, 1));
}
