#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int n;
int p[N];
int a;
int res;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        p[a-1] = i;
    }

    int ls = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] < p[i-1]) {
            res = max(res, i-ls);
            ls = i;
        }
    }
    res = max(res, n-ls);

    printf("%d\n", n-res);
}
