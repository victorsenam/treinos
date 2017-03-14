#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 112345;
int a[N];
int n, k;

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%d", a+i);

    for (int i = 0; i < k; i++)
        for (int j = i+1; j < n; j++)
            if (a[i] > a[j]) swap(a[i], a[j]);
    printf("%d\n", a[k-1]);
}
