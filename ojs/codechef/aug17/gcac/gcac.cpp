#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3+7;

int n, m, ts;
int mins[N];
int sal[N];
int qt[N];
int p[N];
char qual[N];
bool ok[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;

    while (ts--) {
        cin >> n >> m;

        int rs = 0, nt = m;
        ll tot = 0;

        for (int i = 0; i < n; i++)
            cin >> mins[i];
        for (int i = 0; i < m; i++) {
            cin >> sal[i] >> qt[i];
            ok[i] = 0;
            p[i] = i;
        }

        sort(p,p+m, [] (int i, int j) {
            return sal[i] > sal[j];
        });

        for (int i = 0; i < n; i++) {
            cin >> qual;
            for (int _j = 0; _j < m; _j++) {
                int j = p[_j];
                if (qual[j] == '0') continue;
                if (qt[j] <= 0) continue;
                if (sal[j] < mins[i]) continue;
                tot += sal[j];
                if (!ok[j]) {
                    nt--;
                    ok[j] = 1;
                }
                rs++;
                qt[j]--;
                break;
            }
        }

        cout << rs << " " << tot << " " << nt << endl;
    }
}
