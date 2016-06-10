#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100030;

int a[N];
int n, m, k;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a+i);
    scanf("%d", &m);
    for (int i = n; i < n+m; i++) {
        scanf("%d", a+i);
        for (int j = i; j > 0 && a[j] < a[j-1]; j--)
            swap(a[j], a[j-1]);
    }
    scanf("%d", &k);

    int i = 0;
    int j = 0;
    int maxi = 0;
    while (i < n+m) {
        while (j+1 < n+m && a[j+1] - a[i] <= k) j++;
        maxi = max(maxi, a[j]-a[i]);
        i++;
    }
    for (int i = 0; i < n+m; i++)
        printf("%d ", a[i]);
    printf("\n%d\n", maxi);
}
