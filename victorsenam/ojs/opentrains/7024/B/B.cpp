#include <bits/stdc++.h>
//#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#define debug(...) {}

using namespace std;
typedef long long int ll;
typedef double db;

const int N = 257;
const int M = 2e4+7;
const double eps = 1e-8;

struct disc {
    ll w, t, dt;
};

struct cont {
    double t, dt;

    bool operator < (const cont & ot) const
    { return t < ot.t; }
};

int n[2];
ll w;
disc dv[N];
cont cv[N];
double ans[M];
ll memo[N][M];

struct cvx {
    struct it {
        ll a, b, c;
        int sh;
        ll frm;
    };

    vector<it> st;

    void clear () {
        st.clear();
    }

    ll get (ll x, const it & u)
    { return (x-u.sh)*(x-u.sh-1)*u.a/2 + (x-u.sh)*u.b + u.c; }

    ll get (ll x) {
        if (st.empty()) 
            return LLONG_MIN;
        int lo = 0;
        int hi = st.size()-1;

        while (lo < hi) {
            int mid = (lo+hi+1)/2;
            
            if (st[mid].frm > x)
                hi = mid-1;
            else
                lo = mid;
        }

        return get(x, st[lo]);
    }

    ll getfrm (const it & u) {
        ll lo = 0;
        ll hi = M+M;
        
        while (hi - lo > eps) {
            ll mid = (lo+hi)/2;

            if (get(mid, u) >= get(mid))
                hi = mid;
            else
                lo = mid+1;
        }

        return lo;
    }

    void add (it & u) {
        if (u.c == LLONG_MIN)
            return;

        if (!st.size())
            u.frm = 0;
        else
            u.frm = getfrm(u);

        if (u.frm > M)
            return;

        while (st.size() && st.back().frm >= u.frm)
            st.pop_back();

        st.push_back(u);
    }
} trk[M];

int main () {
    int q;
    scanf("%d %lld", &q, &w);

    while (q--) {
        char c;
        scanf(" %c", &c);
        if (c == 'D') {
            scanf("%lld %lld %lld", &dv[n[0]].w, &dv[n[0]].t, &dv[n[0]].dt);
            n[0]++;
        } else {
            scanf("%lf %lf", &cv[n[1]].t, &cv[n[1]].dt);
            n[1]++;
        }
    }
    
    sort(cv, cv+n[1]);

    double currpos = 0.;
    int r = n[1]-1;

    if (n[1]) {
        for (int cw = 1; cw <= w;) {
            double tonxt = 0.;
            tonxt = 1./0.;
            if (r) {
                tonxt = (cv[r].t - cv[r-1].t)/cv[r].dt;

                if (tonxt <= 1e-9) {
                    cv[r-1].dt = (cv[r-1].dt*cv[r].dt)/(cv[r-1].dt + cv[r].dt);
                    r--;
                    //debug("change to %d at %.6f\n", r, currpos);
                    continue;
                }
            }

            double mv = min(tonxt, cw - currpos);
            currpos += mv;
            ans[cw] += mv * cv[r].t - .5 * mv * mv * cv[r].dt;
            cv[r].t -= mv * cv[r].dt;
            //debug("%.6f : [%d = %.6f]\n", currpos, cw, ans[cw]);

            if (currpos >= cw) {
                cw++;
                ans[cw] = ans[cw-1];
            }
        }
    } else {
        for (int cw = 1; cw <= w; cw++)
            ans[cw] = -1./0.;
    }

    for (int i = 0; i <= n[0]; i++) {
        if (!i) {
            memo[i][0] = 0.;
            for (int dw = 1; dw <= w; dw++)
                memo[i][dw] = LLONG_MIN;
        } else {
            for (int dw = 0; dw < dv[i-1].w; dw++) {
                trk[dw].clear();
            }

            for (int dw = 0; dw <= w; dw++) {
                debug("%d %d class %d\n", i, dw, dw%dv[i-1].w);
                cvx::it u;
                u.sh = dw/dv[i-1].w;
                u.a = -dv[i-1].dt;
                u.b = dv[i-1].t;
                u.c = memo[i-1][dw];

                trk[dw%dv[i-1].w].add(u);
                memo[i][dw] = trk[dw%dv[i-1].w].get(dw/dv[i-1].w);
            }
        }
    }

    double res = -1./0.;
    for (int dw = 0; dw <= w; dw++) {
        //debug("%d : %.6f %.6f\n", dw, memo[n[0]][dw], ans[w-dw]);
        if (memo[n[0]][dw] == LLONG_MIN || ans[w-dw] == -1./0.)
            continue;
        res = max(res, double(memo[n[0]][dw]) + ans[w-dw]);
    }

    if (res == -1./0.)
        printf("impossible\n");
    else
        printf("%.20f\n", res);
}
