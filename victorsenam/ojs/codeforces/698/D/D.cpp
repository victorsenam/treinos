#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1007;
const int K = 8;
const int L = (1<<K);

inline ll sq (ll x) {
    return x*x;
}

struct point {
    ll x, y;

    inline ll dist (point ot) {
        return sq(ot.x-x) + sq(ot.y-y);
    }

    inline ll cross (point ot) {
        return (ot.x*y - ot.y*x);
    }

    inline ll cmpang (point a, point b) {
        point p;
        p.x = x;
        p.y = y;
        ll res = (p-a).cross(p-b);
        return res;
    }

    inline bool islin (point a, point b) {
        point p;
        p.x = x; p.y = y;
        if ((a.x>p.x)^(b.x>p.x)) return 0;
        return (p.cmpang(a, b) == 0);
    }

    point operator - (point ot) {
        point p;
        p.x = x - ot.x;
        p.y = y - ot.y;
        return p;
    }
};

int pos[K][N];
int p[K][N];
point a[K];
point m[N];
int ch[K][K];
int memo[K][N][L];
int piv;
int n, k;
int can[N];

bool cmp_t (int i, int j) {
    if ((m[i].x>a[piv].x)^(m[j].x>a[piv].x))
        return m[i].x < m[j].x;

    if (a[piv].cmpang(m[i], m[j]) != 0)
        return a[piv].cmpang(m[i], m[j]) < 0;

    return a[piv].dist(m[i]) < a[piv].dist(m[j]);
}

int buildfrom (int a, int b) {
    int i = 0;
    int j = 0;
    int res = 0;

    while (i < k && j < k) {
        while (i < k && !((1<<i)&a)) i++;
        if ((1<<j)&b)
            res |= (1<<i);
        j++; i++;
    }
    return res;
}

int pd (int j, int i, int msk) {
    int & me = memo[j][i][msk];
    if (me != 0) return (me > 0);
    
    me = 0;

    int ps = pos[j][i];
    if (ps == 0) me = 1;
    if (!me) {
        int prev = p[j][ps-1];
        if (!a[j].islin(m[prev], m[i])) me = 1;

        for (int mask = 1; !me && (mask < (1<<__builtin_popcount(msk))); mask++) {
            int nm = buildfrom(msk, mask);
            assert((nm&msk) == nm);
            for (int r = 0; !me && r < k; r++) {
                if ((1<<r)&nm)
                    me |= (pd(r, prev, (nm&(~(1<<r)))) && pd(j, prev, (msk&(~nm))));
            }
        }

        for (int r = 0; !me && r < k; r++) {
            if ((1<<r)&msk && m[prev].islin(a[j], a[r]) && !ch[j][r])
                me |= (pd(r, prev, (msk&(~(1<<r)))));
        }
    }
    if (me == 0) me--;
    //DEBUG("%d %d %s -> %d\n", j, i, bitset<3>(msk).to_string().c_str(), me > 0);
    return (me > 0);
}

int main () {
    scanf("%d %d", &k, &n);

    int msk = 0;
    for (int i = 0; i < k; i++) {
        scanf("%lld %lld", &a[i].x, &a[i].y);
        msk |= (1<<i);
    }

    for (int i = 0; i < n; i++) 
        scanf("%lld %lld", &m[i].x, &m[i].y);

    for (int j = 0; j < k; j++) {
        for (int i = 0; i < n; i++)
            p[j][i] = i;

        //DEBUG("from (%lld,%lld)\n", a[j].x, a[j].y);

        piv = j;
        sort(p[j], p[j] + n, cmp_t);
        for (int i = 0; i < n; i++) {
            //if (i && !a[j].islin(m[p[j][i-1]],m[p[j][i]]))
                //DEBUG("-\n");
            //DEBUG("%d : (%lld,%lld)\n", i, m[p[j][i]].x, m[p[j][i]].y);
            pos[j][p[j][i]] = i;
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = i+1; j < k; j++)  {
            for (int mi = 0; mi < n; mi++)
                if (a[i].islin(m[mi], a[j]) && a[j].islin(m[mi], a[i]))
                    ch[i][j] = 1;
            ch[i][j] = ch[j][i];
        }
    }

    int cnt =0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++)
            can[i] |= pd(j, i, (msk&(~(1<<j))));
        cnt += can[i];
        if (can[i]) {
            DEBUG("(%lld,%lld)\n", m[i].x, m[i].y);
        }
    }


 //   DEBUG("%d\n", pd(1, 3, (msk&(~2))));
    printf("%d\n", cnt);
}
