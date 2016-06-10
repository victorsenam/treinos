#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1007;

int a[N];
int n;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a+i);

    for (int i = 0; i < n; i++)
        for (int j = i; j > 0 && a[j] < a[j-1]; j--)
            swap(a[j], a[j-1]);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
