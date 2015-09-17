#include <bits/stdc++.h>

using namespace std;

int pi, ti;
int pd, td;

int main () {
    scanf("%d %d %d %d", &pi, &pd, &ti, &td);

    while (pi < ti) {
        pi += pd;
        ti -= td;
    }
    printf("%d\n", max(pi, ti));
}
