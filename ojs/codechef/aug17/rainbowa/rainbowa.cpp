#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 203;

int a[8];
int v[N];
int n, ts;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        cin >> n;

        bool ok = 1;
        int ls = 1;
        bool dsc = 0;

        for (int i = 0; i < n; i++) {
            cin >> v[i];
            
            if (v[i] == ls) {
                a[ls]++;
            } else if (v[i] > ls) {
                if (dsc || v[i] > ls + 1)
                    ok = 0;
                else {
                    ls = v[i];
                    if (ls == 7)
                        dsc = 1;
                }
            } else {
                if (!dsc || v[i] < ls - 1)
                    ok = 0;
                else
                    ls = v[i];
            }

            if (i > n - i - 1 && v[i] != v[n-i-1])
                ok = 0;
        }

        if (ls != 1 || !dsc)
            ok = 0;

        if (ok)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}
