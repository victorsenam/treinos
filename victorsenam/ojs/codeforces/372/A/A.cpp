#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

const int N = 500007;

int a[N];
int n;
int r;
int i, j;

int main () {
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", a+i);
    }

    sort(a, a+n);

    j = n/2-1;
    for (int i = n-1; j >= 0; i--, j--, r++) {
        while (j >= 0 && a[j]+a[j] > a[i]) j--;
        if (j < 0) break;
    }

    printf("%d\n", n-r);
}
