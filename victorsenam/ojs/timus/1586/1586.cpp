#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int D = 10002;
const int N = 100;
const int PRI = 1000;
const num MOD = 1000000009ll;

num memo[D][N];
bool sieve[PRI];
num pot[D];
int n;

num pd (int dig, int pri) {
    int aux;
    if (dig == 0)
        return 1;
    if (memo[dig][pri] != -1)
        return memo[dig][pri];

    memo[dig][pri] = 0;
    for (int i = 0; i <= 9; i++) {
        aux = pri*10 + i;
        if (aux > 99 && !sieve[aux]) {
            memo[dig][pri] += pd(dig-1, aux%100);
            memo[dig][pri] %= MOD;
        }
    }
    return memo[dig][pri];
}

int main () { 
    scanf("%d", &n);
    pot[0] = 1ll;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < N; j++)
            memo[i][j] = -1ll;
        if (i)
            pot[i] = (pot[i-1]*10ll)%MOD;
    }

    sieve[0] = sieve[1] = 1;
    for (int i = 2; i < PRI; i++) {
        if (sieve[i])
            continue;
        for (int j = 2*i; j < PRI; j += i)
            sieve[j] = 1;
    }
    
    num res = 0ll;

    for (int i = 10; i < 100; i++) {
        res = (res+pd(n-2, i))%MOD;
    }
    printf("%lld\n", res);
}
