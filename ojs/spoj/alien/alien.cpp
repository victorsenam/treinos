#include <bits/stdc++.h>

using namespace std;

#define MAX 100000

int t, e, p, q[MAX], sum;
int f, maxd, minp, s=0;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &e, &p);
        for (int i = 0; i < e; i++) {
            scanf("%d", &(q[i]));
        }
        f = e;
        s = 0;
        maxd = 0;
        minp = 0;
        for (int i = e-1; i >= 0; i--) {
            s += q[i];
            while (s > p) {
                f--;
                s-=q[f];
            }
            if (f-i > maxd || (f-i == maxd && s < minp)) {
                maxd = f-i;
                minp = s;
            }
        }
        printf("%d %d\n", minp, maxd);
    }
}
