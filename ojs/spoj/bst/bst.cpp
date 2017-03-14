#include <bits/stdc++.h>

using namespace std;

#define debug(...) { printf(__VA_ARGS__); }

struct el {
    int x;
    long long d;

    inline bool operator < (const el & ot) const
    { return x < ot.x; }
};


const int N = 300007;
int n;
set<el> s;
set<el>::iterator lo, hi;
el aux;
long long cn;

int main () {
    scanf("%d", &n);

    cn = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &aux.x);
        lo = s.lower_bound(aux);
        hi = s.upper_bound(aux);

        if (s.size() == 0) {
            aux.d = 0ll;
        } else if (lo == s.begin()) {
            aux.d = s.begin()->d+1;
        } else {
            --lo;
            if (hi == s.end()) {
                aux.d = lo->d+1;
            } else {
                aux.d = max(lo->d, hi->d) + 1;
            }
        }
        cn += aux.d;
        printf("%lld\n", cn);
        s.insert(aux);
    }
}
