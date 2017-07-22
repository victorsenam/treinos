#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 212345;
int r[N], m[N];

#define printf(args...) ((void) 0)

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, n;
    cin >> n;
    int cm = 0, cr = 0;
    int on = n;
    for(i = 0; i < n; i++) {
        cin >> m[i] >> r[i];
        cm += (m[i] > r[i]);
        cr += (r[i] >= m[i]);
    }
    if(cm > on / 2) { cout << "0\n"; return 0; }
    printf("cm %d cr %d\n", cm, cr);
    vector<int> mvs;
    for(i = 0; i < n - 1 && cm <= (on / 2); i++) {
        if((r[i] >= m[i]) && (r[i + 1] >= m[i + 1])) {
            printf("mv %d\n", i);
            mvs.pb(i);
            i++; on--;
            continue;
        }
        if((((m[i] > r[i]) && (r[i + 1] >= m[i + 1])) || ((r[i] >= m[i]) && (m[i + 1] > r[i + 1])))
            && (m[i] + m[i + 1] > r[i] + r[i + 1])) {
            printf("mv2 %d\n", i);
            mvs.pb(i);
            i++; on--;
            continue;
        }
    }
    if(cm <= (on / 2)) cout << "-1\n";
    else {
        cout << mvs.size() << '\n';
        for(int i : mvs)
            cout << i + 1 << ' ' << i + 2 << '\n';
    }
}
