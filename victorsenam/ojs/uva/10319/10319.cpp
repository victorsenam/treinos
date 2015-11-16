// INCOMPLETO
#include <bits/stdc++.h>

using namespace std;

const int N = 300;
const int M = 1000;

int hd[N], to[M], nx[M], es;
int as, bs, n, t;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d ", &as, &bs, &n);

        for (int i = 0; i < n; i++) {
            int a[2], b[2];
            scanf("%d %d %d %d", a, b, a+1, b+1);

            for (int k = 0; k < 2; k++) {
                a[k] <<= 1;
                b[k] += as;
                b[k] <<= 1;
            }

            if (a[0] == a[1]) {
                if (b[0] < b[1])
                    a[0] |= 1;
                connect(a[0]^1, a[0]);
            } else if (b[0] == b[1]) {
                if (a[0] < a[1])
                    a[0] |= 1;
                connect(b[0]^1, b[0]);
            } else {
                for (int k = 0; k < 2; k++) {
                    if (a[0] < a[1])
                        b[k] |= 1;
                    if (b[0] < b[1])
                        a[k] |= 1;

                    connect(
                }
            }
        }
    }
}
