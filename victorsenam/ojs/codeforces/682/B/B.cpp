#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 100007;

int n;
int a[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i <n ; i++) {
        scanf("%d", a+i);
    }

    sort(a, a+n);

    int nx = 1;
    for (int i = 0; i < n; i++) {
        if (a[i] >= nx)
            nx++;
    }

    printf("%d\n", nx);
}
