#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

int p[3123];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, n;
    cin >> n;
    for(i = 0; i < n; i++)
        cin >> p[i];
    sort(p, p + n);
    int ct = 1;
    int val = p[n - 1];
    for(i = 0; i < n - 1; i++) {
        if(val >= p[i]) {
            val -= p[i];
            ct++;
        }
    }
    cout << ct << '\n';
}
