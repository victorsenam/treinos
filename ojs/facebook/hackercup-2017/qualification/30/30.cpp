#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 102;

int t;
int n;
int w[N];

int main () {
    scanf("%d", &t);

    int tc = 0;
    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &w[i]);
        }

        sort(w, w+n);

        int l = 0;
        int res = 0;

        for (int i = n-1; i >= 0; i--) {
            l += 49/w[i];
            if (l > i) break;
            res++;
        }

        printf("Case #%d: %d\n", ++tc, res);
    }
}
