#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 60;

ll memo[N][2];
int visi[N][2];
ll x, y;

ll pd (int i, int c) {
    if (i == N) return !c;

    ll & me = memo[i][c];
    if (visi[i][c]) return me;
    visi[i][c] = 1;

    me = 0;

    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            if ((a^b) != !!(x&(1llu<<i)))
                continue;
            if ((a+b+c)%2 != !!(y&(1llu<<i)))
                continue;

            me += pd(i+1, (c+a+b)/2);
        }
    }

    return me;
}

int main () {
    scanf("%lld %lld", &y, &x);

    printf("%lld\n", pd(0,0) - 2*(y==x));
}
