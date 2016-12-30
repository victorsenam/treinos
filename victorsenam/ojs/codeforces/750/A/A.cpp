#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

int n, k;

int main () {
    scanf("%d %d", &n, &k);
    k = 240 - k;

    int res = 0;
    for (int i = 1; i <= n; i++) {
        k -= 5*i;
        if (k < 0) break;
        res++;
    }

    printf("%d\n", res);
}
