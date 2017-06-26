#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug if(true)
#else
#define debug if(false)
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
double eps = 1e-8;

int n;
double t;
double d[N], s[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> t;

    double lo = -1e9;
    double hi = 1e9;
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> s[i];
        lo = max(lo, -s[i]);
    }

    while (hi - lo > eps) {
        double c = .5*(lo+hi);
        double qt = 0.;
        for (int i = 0; i < n; i++)
            qt += d[i]/(s[i]+c);
        if (qt < t)
            hi = c;
        else
            lo = c;
    }

    cout << setprecision(20) << lo << endl;    
}
