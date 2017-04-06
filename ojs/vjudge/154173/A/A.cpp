#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 3e3+7;

struct vect {
    ll x, y;
    vect (ll a=0, ll b=0) : x(a), y(b) {}

    bool operator < (const vect & ot) const
    { return (x < ot.x) || (x == ot.x && y < ot.y); }

    ll operator ^ (const vect & ot) const
    { return x*ot.x + y*ot.y; }
    ll operator * (const vect & ot) const
    { return x*ot.y - y*ot.x; }

    vect operator - (const vect & ot) const
    { return vect(x - ot.x, y - ot.y); }

    ll area (const vect & a, const vect & b) const
    { return ((*this) - a)*((*this) - b); }
    ll sq (const vect & ot) const
    { return ((*this) - ot)^((*this) - ot); }
};

int t, n;
vect v[N];
vect s[N];
int st;

inline ll sol (int i, int j, int k) {
    return abs(v[i].area(v[j],v[k]));
}

ll go (int i, int j) {
    int lo = i+1;
    int hi = j-1;

    ll res = 0;
    while (lo + 3 < hi) {
        int q1 = (lo + lo + hi)/3;
        int q2 = (lo + hi + hi)/3;

        res = max(res, sol(i,j,q1));
        res = max(res, sol(i,j,q2));

        if (sol(i, j, q1) < sol(i, j, q2))
            lo = q1+1;
        else
            hi = q2-1;
    }

    while (lo <= hi) {
        res = max(res, sol(i,j,lo));
        lo++;
    }

    return res;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &v[i].x, &v[i].y);
            if (v[i] < v[0])
                swap(v[i], v[0]);
        }
        
        vect anc = v[0];
        sort(v+1, v+n, [anc] (vect a, vect b)  { 
            ll ar = anc.area(a,b);
            if (ar == 0)
                return anc.sq(a) < anc.sq(b);
            return anc.area(a,b) > 0; 
        });

        s[0] = v[0];
        s[1] = v[1];
        st = 2;
        
        for (int i = 2; i < n; i++) {
            s[st] = v[i];
            while (st > 1 && s[st-2].area(s[st-1], s[st]) <= 0) {
                swap(s[st-1], s[st]);
                st--;
            }
            st++;
        }

        n = st;
        for (int i = 0; i < n; i++) {
            v[i+n] = v[i] = s[i];
        }

        ll rs = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                rs = max(rs, go(i,j) + go(j,i+n));
            }
        }


        print("%lld", rs/2);
        if (rs%2)
            printf(".5");
        printf("\n");
    }
}
