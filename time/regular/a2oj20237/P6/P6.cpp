#include <bits/stdc++.h>

using namespace std;

const int N = 35;
const int K = 2;

typedef unsigned long long int num;

num memo[N][K];
num vis[N][K];
num turn;

num n, m, res;

num pd (int dig, int free){ 
    if (dig == 0)
        return (free||(n%2));
    if (vis[dig][free] == turn)
        return memo[dig][free];
    
    vis[dig][free] = turn;
    num & m = memo[dig][free];
    if (free)
        m = pd(dig-1, 1) + pd(dig-1, 1) + (1llu<<dig);
    else if (n&(1llu<<dig))
        m = pd(dig-1, 0) + (n%(1llu<<dig)) + 1llu + pd(dig-1, 1);
    else
        m = pd(dig-1, 0);

    return m;
}

int main () {
    int ts;
    while(scanf("%llu %llu", &m, &n) != EOF && (m || n)) {
        res = 0;

        if (n > 0) {
            turn++;
            res = pd(34, 0);
        }

        if (m > 1) {
            n = m-1;
            turn++;
            res -= pd(34, 0);
        }

        printf("Case %d: %llu\n", ++ts, res);
    }
}
