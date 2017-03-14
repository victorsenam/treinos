#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const num MOD = 1000000007ll;
const int N = 100007;

num memo[N][2];
bool visi[N][2];
int n;
num solve (int i, bool ok) {
    if (i == n)
        return (num) ok;

    if (visi[i][ok])
        return memo[i][ok];
    visi[i][ok] = 1;

    return (memo[i][ok] = ((solve(i+1, 1)*20llu)%MOD + (solve(i+1, ok)*7llu)%MOD)%MOD);
}

int main () {
    scanf("%d", &n);

    printf("%d\n", (int) solve(0, 0));
}
