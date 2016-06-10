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
int h;
int a;
int s;

int main () {
    scanf("%d %d", &n, &h);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        s += 1 + (a > h);
    }
    printf("%d\n", s);
}
