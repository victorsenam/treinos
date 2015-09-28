#include <bits/stdc++.h>

using namespace std;

const int N = 100006;

int n;
int a[N];
int maxi[N];
int q;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", a+i);

    maxi[n] = 0;
    for (int i = 0; i < n; i++)
        maxi[n-1-i] = max(maxi[n-i], a[n-1-i]);

    for (int i = 0; i < n; i++) {
        printf("%d ", max(0, maxi[i+1]-a[i]+1));
    }
}
