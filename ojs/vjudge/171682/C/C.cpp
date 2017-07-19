#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define double long double

struct vec {
    double x, y;

    vec () : x(0), y(0) {}
    vec (double a, double b) : x(a), y(b) {}

    double operator * (vec o) {
        return x*o.x + y*o.y;
    }
    vec operator - (vec o) {
        return vec(x - o.x, y - o.y);
    }
    vec operator + (vec o) {
        return vec(x + o.x, y + o.y);
    }
    vec operator * (double a) {
        return vec(x*a, y*a);
    }
    vec operator / (double a) {
        return vec(x/a, y/a);
    }

    double sq (vec o) {
        return ((*this) - o)*((*this) - o);
    }
    double nr (vec o) {
        return sqrt(((*this) - o)*((*this) - o));
    }

    vec sobe () {
        return vec(-y,x);
    }
};

const int N = 53;
const double eps = 1e-9;

int ts, n;
vec w[N];
double s[N];

double sq (double x) {
    return x*x;
}

bool tenta (vec x, double t) {
    for (int i = 0; i < n; i++)
        if (x.nr(w[i]) > t*s[i] + eps)
            return 0;
    return 1;
}

bool solve (double t) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            double d = w[i].nr(w[j]);
            if (d > s[i]*t + s[j]*t + eps)
                continue;
            double x = ((sq(s[i]*t) - sq(s[j]*t))/(2.*d)) + (d/2.);
            double a = sqrt(max(sq(s[i]*t) - sq(x), 0.L));

            vec s = (w[j] - w[i])/d;
            vec p = w[i] + (s*x);
            if (tenta(p + (s.sobe()*a), t)) return 1;
            if (tenta(p - (s.sobe()*a), t)) return 1;
            p = w[i] - (s*x);
            if (tenta(p + (s.sobe()*a), t)) return 1;
            if (tenta(p - (s.sobe()*a), t)) return 1;
        }
        if (tenta(w[i], t)) return 1;
    }
    return 0;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> ts;
    while (ts--) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> w[i].x >> w[i].y >> s[i];
        
        
        double lo = 0.;
        double hi = 1e8;
        
        for (int its = 0; its <= 100; its++) {
            double mid = .5*(lo+hi);
            if (solve(mid))
                hi = mid;
            else
                lo = mid;
        }

        cout << setprecision(20) << lo << endl;
    }
}
