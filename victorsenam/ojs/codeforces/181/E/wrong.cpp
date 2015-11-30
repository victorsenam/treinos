#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 5;
const int L = 4;
const int M = (1llu<<(N*L));

struct bm {
    num x;

    bm () : x(0) {}
    bm (num a) : x(a) {}
    
    operator num() const
    { return x; }

    inline bool get (int i, int j)
    { return (x&(num(1)<<(i*N+j))); }
    inline void set (int i, int j)
    { x |= (num(1)<<(i*N+j)); }
    inline void unset (int i, int j)
    { x &= (~(num(1)<<(i*N+j))); }

    bm lrow(int n) {
        bm res(0llu);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < L; j++)
                if (get(i, j))
                    res.set(i, j);
        return res;
    }
    bm frow(int n) 
    { return bm(x>>N); }

    bm lcol(int n) {
        bm res(0llu);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < n; j++)
                if (get(i, j))
                    res.set(i, j);
        return res;
    }
    bm fcol(int n)
    { return bm(x>>1).lcol(n); }
};

bool memo[N][N][M][2];
bool visi[N][N][M][2];

bool dp (int n, int m, num mask, bool ty) {
    bm st(mask);

    if (visi[n][m][mask][ty])
        return memo[n][m][mask][ty];
    visi[n][m][mask][ty] = 1;
    bool & me = memo[n][m][mask][ty];
    me = !ty;

    if (ty) {
        if (n) {
            if (!st.get(0, 0)) {
                bm aux = st.frow(n);
                me |= dp(n-1, m, num(aux), 0);
            }
            if (!st.get(n, m)) {
                bm aux = st.lrow(n);
                me |= dp(n-1, m, num(aux), 0);
            }
        }
        if (m) {
            if (!st.get(0, 0)) {
                bm aux = st.fcol(m);
                me |= dp(n, m-1, num(aux), 0);
            }
            if (!st.get(n, m)) {
                bm aux = st.lcol(m);
                me |= dp(n, m-1, num(aux), 0);
            }
        }
    } else {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (!st.get(i, j) || (i == 0 && j == 0) || (i == n && j == m))
                    continue;
                st.set(i, j);
                me &= dp(n, m, num(st), 1);
                st.unset(i, j);
            }
        }
    }

    return me;
}

int main () {
    int n, m;
    int x, y;

    scanf("%d %d", &n, &m);
    scanf("%d %d", &n, &m);
    scanf("%d %d", &x, &y);

    n -= x;
    if (n < 0)
        n = -n;

    m -= y;
    if (m < 0)
        m = -m;

    if ((n == 4 && m == 4) || max(n, m) > 4 || !dp(min(n, m), max(n, m), num(0), 1))
        printf("Second\n");
    else
        printf("First\n");

}
