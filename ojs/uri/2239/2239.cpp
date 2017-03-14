#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const ll MOD = 1e9+7;
const int K = 16;
const int N = (1<<K);

ll memo[N][4];
ll fat[20];
char str[5*K][12];
int n;

int get (char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    return c - 'a' + 10;
}

char send (int v) {
    if (v < 10)
        return '0' + v;
    return 'a' + v - 10;
}

void printit (ll v) {
    int s = 0;
    
    if (!v)
        str[n][s++] = '0';

    while (v) {
        str[n][s++] = send(v&((1<<4)-1));
        v >>= 4;
    }

    for (int i = s-1; i >= 0; i--)
        putchar(str[n][i]);
}

ll calc (int mask, int k) {
    ll r = 0;
    for (int i = 0; str[k][i]; i++) {
        if (mask&(1<<get(str[k][i]))) continue;
        r <<= 4;
        r = (r + get(str[k][i]));
    }
    return r;
}

ll calc (int mask) {
    ll & res = memo[mask][3];
    if (res != -1) return res;
    res = 0;
    for (int i = 0; i < n; i++)
        res = (res + calc(mask, i));
    return res;
}

ll pd (int mask) {
    if (mask == N-1)
        return 0;

    ll & me = memo[mask][2];
    if (me != -1) return me;
    
    int cc = 16 - __builtin_popcount(mask);
    me = 0;
    if (mask)
        me = calc(mask)%MOD;
    me = (me * fat[cc]);

    for (int i = 0; i < 16; i++) {
        if (mask&(1<<i)) continue;

        me = (me + pd(mask|(1<<i)))%MOD;
    }

    return me;
}

bool compare (int st, ll a, ll b) {
    if (st == 0) return a <= b;
    if (st == 1) return a >= b;
}

ll get (int mask, int st) {
    if (mask == N-1) return 0;

    ll & me = memo[mask][st];
    if (me != -1) return me;

    for (int i = 0; i < 16; i++) {
        if (mask&(1<<i)) continue;

        int nm = (mask|(1<<i));
        ll loc = calc(nm) + get(nm, st);
        if (me == -1 || compare(st, loc, me))
            me = loc;
    }

    return me;
}

int main () {
    scanf(" %s", &str[0]);
    n = calc(0,0);

    fat[0] = 1;
    for (ll i = 1; i < 18; i++)
        fat[i] = (fat[i-1]*i)%MOD;

    memset(memo, -1, sizeof memo);
    for (int i = 0; i < n; i++) {
        scanf(" %s", &str[i]);
    }

    int mask = 0;
    ll res = 0;

    printit(get(0,0));
    putchar(' ');
    printit(get(0,1));
    putchar(' ');
    printit(pd(0));
    putchar('\n');
}

