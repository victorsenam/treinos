#include <bits/stdc++.h>

using namespace std;

int pi, ti;
int pd, td;

int main () {
    scanf("%d %d %d %d", &pi, &pd, &ti, &td);
    
    if (pi >= ti) {
        printf("%d\n", pi);
        return 0;
    }
    while (42) {
        pi += pd;
        if (pi >= ti) {
            printf("%d\n", ti);
            return 0;
        }
        ti -= td;
        if (pi >= ti) {
            printf("%d\n", pi);
            return 0;
        }
    }
}
