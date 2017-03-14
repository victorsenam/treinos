#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 1000007;

num x;
num res[N][2];

inline num calc (num n, num m) {
    return n*n*m - (n+m)*n*(n-1)/2 + (n-1)*(n)*(2*(n-1)+1)/6;
}

inline num bs (num n, num lo, num hi) {
    if (lo == hi)
        return (calc(n, lo) == x)?lo:0;

    num mid = lo+(hi-lo)/2;

    num val = calc(n, mid);

    if (val < x)
        return bs(n, mid+1, hi);
    return bs(n, lo, mid);
}

int main () {
    scanf("%llu", &x);
    
    int cnt = 0;
    for (num i = 1; i*i*i <= 3*x; i++) {
        num r = bs(i, 0, x/i*i+1);
        if (r != 0) {
            res[cnt][0] = i;
            res[cnt++][1] = r;
        }
    }

    printf("%d\n", 2*cnt);
    for (int i = 0; i < cnt; i++)
        printf("%llu %llu\n", res[i][0], res[i][1]);
    for (int i = cnt-1; i >= 0; i--)
        printf("%llu %llu\n", res[i][1], res[i][0]);
}
