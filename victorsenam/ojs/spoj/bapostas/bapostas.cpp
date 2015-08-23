#include <bits/stdc++.h>

#define N 10000

int n, v[N], maxs[N], maxi, a, b;

inline int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int main () {
    assert(INT_MAX > N);

    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
        }

        maxs[n-1] = max(0, v[n-1]);
        for (int i = n-2; i >= 0; i--) {
            maxs[i] = max(0, max(v[i], v[i]+maxs[i+1]));
        }

        maxi = 0;
        for (int i = 0; i < n; i++) {
            if (maxs[i] > maxi) maxi = maxs[i];
        }

        if (maxi) printf("The maximum winning streak is %d.\n", maxi);
        else printf("Losing streak.\n");
    }
}
