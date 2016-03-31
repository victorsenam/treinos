#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef unsigned int ui;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int K = 15;
const int N = (1<<K);
const int M = 107;

bool memo[N][M];
int visi[N][M], turn;
int n, x, y;
int v[K];
int arr[N];
vector<ui> siz[K];

bool dp (ui mask, int w);

bool dp (ui mask, int w) {
    if (__builtin_popcount(mask) == 1) return 1;
    if (w <= 0) return 0;
    
    //printf("%s\n", (bitset<15>(mask).to_string().c_str()));

    bool & me = memo[mask][w];
    if (visi[mask][w] == turn)
        return me;
    visi[mask][w] = turn;

    me = 0;
    int sz = 0;
    int a = 0;

    for (int i = 0; i < n; i++) {
        if ((1<<i)&mask) {
            a += v[i];
            sz++;
        }
    }

    if (a%w)
        return me;
    
    int h = a/w;
    for (int k = 1; k <= (sz/2); k++) {
        for (int kk = 0; kk < siz[k].size(); kk++) {
            ui tm = siz[k][kk];
            if ((tm|mask) != mask) continue;
            int ar = arr[tm];

            if (ar%w == 0 && (a-ar)%w == 0) {
                me = ((dp(tm, w) || dp(tm, ar/w)) && (dp(mask^tm, w) || dp(mask^tm, (a-ar)/w)));
                if (me) return me;
            }
        }
    }
    return me;
}

int main () {
    int x, y, a;

    for (ui i = 1; i < N; i++)
        siz[__builtin_popcount(i)].push_back(i);

    while (scanf("%d", &n) != EOF && n) {
        ++turn;
        a = 0;
        scanf("%d %d", &x, &y);
        for (int i = 0; i < n; i++) {
             scanf("%d ", v+i);
             a += v[i];
        }
        sort(v, v+n);
        printf("Case %d: ", turn);
        if (a != x*y)
            printf("No\n");
        else {
            for (ui i = 1; i < (1u<<n); i++) {
                arr[i] = 0;
                for (int j = 0; j < n; j++)
                    if ((1u<<j)&i)
                        arr[i] += v[j];
            }
            if (!dp((1u<<n) - 1, x) && !dp((1u<<n) - 1, y))
                printf("No\n");
            else
                printf("Yes\n");
        }
    }
}
