#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int p, a, b;

int main () {
    scanf("%d %d %d", &p, &a, &b);

    if (p < b) {
        printf("-1\n");
    } else {
        p -= b;
        printf("%d\n", max(a,p) + b);
    }
}
