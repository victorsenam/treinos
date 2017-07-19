#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 52;

int q, n;
int v[N][N][N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> q;
    while (q--) {
        int res = 0;
    
        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) {
                    cin >> v[i][j][k];
                    res += (v[i][j][k] == 1);
                }
        cout << res;

        for (int c = 1; c < n; c++) {
            res = 0;
            for (int i = 0; i + c < n; i++)
                for (int j = 0; j + c < n; j++)
                    for (int k = 0; k + c < n; k++) {
                        for (int l = 1; l < 8; l++)
                            v[i][j][k] = max(v[i][j][k], v[i+!!(l&1)][j+!!(l&2)][k+!!(l&4)]);
                        res += (v[i][j][k] == c+1);
                    }
            cout << " " << res;
        }
        cout << endl;
    }
}
