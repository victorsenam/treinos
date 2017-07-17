#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

int n;
int v[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> n) {
        set<int> s;
        ll cn = 0;
        for (int i = 0; i < n; i++) {
            cin >> v[i];

            if (s.find(v[i]+1) != s.end())
                cn++;
            s.insert(v[i]);
        }

        ll res = 0;
        ll pw = 1;

        while (pw <= cn) {
            res++;
            pw += pw;
        }

        cout << res << endl;
    }
}
