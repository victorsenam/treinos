#include <bits/stdc++.h>

using namespace std;

int n, x;
int lf;
int rf;

int main () {
    scanf("%d %d", &n, &x);

    scanf("%d %d", &lf, &rf);
    if (lf > rf)
        swap(lf, rf);

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        if (a > b)
            swap(a, b);

        lf = max(lf, a);
        rf = min(rf, b);
    }
    
    if (lf > rf)
        printf("-1\n");
    else if (lf <= x && rf >= x)
        printf("0\n");
    else if (rf < x)
        printf("%d\n", x-rf);
    else
        printf("%d\n", lf-x);
}

