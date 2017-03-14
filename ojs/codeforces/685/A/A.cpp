#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef unsigned int ui;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 12;
const int K = (1u<<7);

ll memo[K][N][2][2];
int visi[K][N][2][2], turn;

ll inp;
int n[2][N];
int siz[2];

ll pd (ui mask, int i, bool pre, int b) {
    if (b == 2) return 1;
    if (siz[b] == i) return pd(mask, 0, 0, b+1);

    ll & me = memo[mask][i][pre][b];
    if (visi[mask][i][pre][b])
        return me;
    visi[mask][i][pre][b] = 1;

    me = 0;

    for (int a = 0; a < 7; a++) {
        if (!pre && a > n[b][i]) break;
        if (mask&(1u<<a)) continue;

        me += pd((mask|(1u<<a)), i+1, (pre||(a<n[b][i])), b);
    }

    return me;
}

int main () {

    for (int j = 0; j < 2; j++) {
        scanf("%lld", &inp);
        inp--;

        siz[j] = !inp;

        while (inp) {
            n[j][siz[j]++] = inp%7;
            inp /= 7;
        }



        for (int i = 0; i < siz[j]/2; i++)
            swap(n[j][i], n[j][siz[j]-1-i]);

    }


    printf("%lld\n", pd(0, 0, 0, 0));
}
