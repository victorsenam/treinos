#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

int n;
    cin >> n;
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        if (y == 1)
            a++;
        else
            b++;
    }

    if (a > 11*b || b > 11*a)
        cout << -1 << endl;
    else
        cout << (n+11)/12 << endl;
}

