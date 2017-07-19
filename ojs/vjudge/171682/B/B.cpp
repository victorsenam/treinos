#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;
const int M = 4e6+7;

int ts;
int n, m;
int w[N], l[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        cin >> n >> m;

        for (int i = 0; i < n; i++)
            l[i] = w[i] = 0;

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;

            if (a < b) {
                w[a]++;
                l[b]++;
            } else {
                w[b]++;
                l[a]++;
            }
        }

        bool ok = 0;
        for (int i = n-1; !ok && i >= 0; i--) {
            if (!l[i] && i + w[i] == n-1) {
                cout << 2 << " " << i + 1 << endl;
                ok = 1;
            }
        }

        if (!ok)
            cout << (n > 2) << endl;
    }

}
