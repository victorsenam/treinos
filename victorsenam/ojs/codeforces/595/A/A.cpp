#include <bits/stdc++.h>

using namespace std;

int n, m;

int main () {
    scanf("%d %d", &n, &m);

    int res = 0;
    int a, b;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d %d", &a, &b);
            if (a|b)
                res++;
        }
    }
    printf("%d\n", res);
}
