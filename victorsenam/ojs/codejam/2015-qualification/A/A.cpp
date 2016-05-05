#include <bits/stdc++.h>

using namespace std;

int n, s, p, d, t;
char v;

int main () {
    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        s = p = 0;
        scanf("%d ", &n);
        for (int i = 0; i <= n; i++) {
            scanf("%c", &v);
            if (v > '0') {
                d = max(0, i-s);
                p += d;
                s += d;
            }
            s += (v-'0');
        }
        printf("Case #%d: %d\n", c, p);
    }
}
