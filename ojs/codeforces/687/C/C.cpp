#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 502;

bitset<N> memo[N][N];
bool visi[N][N];
int n, k;
int v[N];

bitset<N> pd (int s, int i) {
    if (s > k || i > n) return 0;
    if (s == k) return 1;

    bitset<N> & me = memo[s][i];

    if (visi[s][i] == 1)
        return me;
    visi[s][i] = 1;

    me = 0;
    bitset<N> loc = pd(s+v[i], i+1);
    if (loc.any()) {
        me |= loc;
        me |= (loc<<v[i]);
    }
    loc = pd(s, i+1);
    if (loc.any()) {
        me |= loc;
    }

    return me;
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%d", v+i);

    bitset<N> res = pd(0, 0);

    printf("%d\n", (int)res.count());
    for (int i = 0; i < N; i++)
        if (res.test(i))
            printf("%d ", i);
    printf("\n");
}
