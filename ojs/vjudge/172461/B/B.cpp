#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3;

int ts;
char str[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        cin >> str;

        int n = strlen(str);
        bool ok = 0;
        if (n == 1) {
            ok = 1;
        } else if (__builtin_popcount(n) == 1) {
            ok = 1;
            for (int i = 0; i < n; i += 2)
                if (str[i] != 'P' && str[i+1] != 'P')
                    ok = 0;
        }

        if (ok)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
