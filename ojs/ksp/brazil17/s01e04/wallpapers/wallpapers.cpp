#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 2e5;

ll w[N][2], h[N][2];
int t, n;
int p[N];

int main () {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> w[i][0] >> w[i][1] >> h[i][0] >> h[i][1];
            p[i] = i;
        }

        sort(p, p+n, [] (int i, int j) {
            if (w[i][0] != w[j][0]) return w[i][0] < w[j][0];
            if (w[i][1] != w[j][1]) return w[i][1] > w[j][1];
            if (h[i][0] != h[j][0]) return h[i][0] < h[j][0];
            return h[i][1] > h[j][1];
        });

        bool ok = 1;
        for (int i = 1; ok && i < n; i++) {
            if (w[p[i]][0] < w[p[0]][0]) ok = 0;
            if (w[p[i]][1] > w[p[0]][1]) ok = 0;
            if (h[p[i]][0] < h[p[0]][0]) ok = 0;
            if (h[p[i]][1] > h[p[0]][1]) ok = 0;
        }

        if (ok)
            cout << "ANO" << endl;
        else
            cout << "NIE" << endl;
    }
}
