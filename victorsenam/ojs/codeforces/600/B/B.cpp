#include <bits/stdc++.h>

using namespace std;

const int N = 200007;

int a[N], b;
int n, m;

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n ; i++) 
        scanf("%d", a+i);

    sort(a, a+n);

    for (int i = 0; i < m ; i++) {
        scanf("%d", &b);
        printf("%d ", upper_bound(a, a+n, b) - a);
    }
}
