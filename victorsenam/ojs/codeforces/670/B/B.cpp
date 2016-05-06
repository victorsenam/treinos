#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int n, k;
int r;

int main () {
    scanf("%d %d", &n, &k);
    int i = 1;
    int v = 0;
    while (v < k) {
        v += i;
        i++;
    }
    i--;

    for (int j = 0; j < i-(v-k); j++)
        scanf("%d", &r);
    printf("%d\n", r);
}
