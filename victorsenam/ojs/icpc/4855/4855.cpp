#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

int fib[60];
int n, a, t, fs;
num res, loc;

int main () {
    fib[0] = 1;
    fib[1] = 2;
    for (fs = 1; fib[fs] > 0; fs++)
        fib[fs+1] = fib[fs-1]+fib[fs];

    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        res = 1;

        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            loc = 0;
            int it = fs-1;
            while (a) {
                while (fib[it] > a)
                    it--;
                loc += a/fib[it];
                a %= fib[it];
 //               printf("%d %d\n", a, fib[it]);
            }
            res *= loc;
        }
        printf("Case %d: %lld\n", c, res);
    }
}
