#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef ll num;
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define debug(...) {}
#endif

const int N = 2000007;

bool sieve[N];
int prime[N];
int p, q, n;

bool checkPal(int v) {
    int hi = 1;
    int lo = 1;
    while (hi <= v)
        hi *= 10;
    hi /= 10;

    while (lo < hi) {
        if ((v/lo)%10 != (v/hi)%10)
            return 0;
        lo *= 10;
        hi /= 10;
    }
    return 1;
}

int main () {
    for (p = 2; p < N; p++) {
        if (sieve[p]) continue;
        prime[p] = 1;
        for (q = 1; q*p < N; q++)
            sieve[p*q] = 1;
    }

    scanf("%d %d", &p, &q);


    int pri, pal;
    pri = pal = 0;

    int n = 1;
    int last = -1;
    while (n < N) {
        if (prime[n]) pri++;
        if (checkPal(n)) pal++;
        
        if ((num)q*(num)pri <= (num)p*(num)pal) {
            last = n;
        }
        n++;
    }

    if (last == -1)
        printf("Palindromic tree is better than splay tree\n");
    else
        printf("%d\n", last);
}
