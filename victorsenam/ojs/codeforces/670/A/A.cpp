#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int n;

int main () {
    scanf("%d", &n);

    printf("%d %d\n", 2*(n/7) + (n%7 == 6), 2*(n/7) + (n%7 >= 1) + (n%7 >= 2));
}
