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

const int N = 1e5+7;
const double eps = 1e-4;

ll v[N][2];
int n;

double solve (double x) {
    double mx = 0.;
    double mn = 1./0.;
    for (int i = 0; i < n; i++) {
        double p = (x - v[i][0])*double(v[i][1]);
        mx = max(mx, p);
        mn = min(mn, p);
    }

    return mx - mn;
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        double lo = 0.;
        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &v[i][0], &v[i][1]);
            lo = max(lo, double(v[i][0]));
        }
        
        double hi = 1e11;

        int q = 150;
        while (q--) {
            double q1 = (lo+lo+hi)/3.;
            double q2 = (lo+hi+hi)/3.;

            if (solve(q1) <= solve(q2))
                hi = q2;
            else
                lo = q1;
        }

        printf("%.20f\n", solve(lo));
    }
}
