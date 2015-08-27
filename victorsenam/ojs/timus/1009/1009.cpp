#include <bits/stdc++.h>

using namespace std;

const int N = 20;
const int K = 12;

typedef unsigned long long int num;

num memo[N][2];
int n, ik;
num k;

num pd (int pos, bool zer) {
    if (pos == 0)
        return 1;

    if (memo[pos][zer] != -1)
        return memo[pos][zer];

    memo[pos][zer] = (k-1)*pd(pos-1, 0);
    if (!zer)
        memo[pos][zer] += pd(pos-1, 1);
    return memo[pos][zer];
}

int main () {
    scanf("%d %d", &n, &ik);

    k = ik;

    memset(memo, -1, sizeof memo);
    printf("%llu\n", (k-1)*pd(n-1, 0));
}
