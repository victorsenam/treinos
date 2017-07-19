#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

int a[2][3];

int main () {
    for (int k = 0; k < 2; k++)
        for (int i = 0; i < 3; i++)
            cin >> a[k][i];

    int r[2] = {0,0};
    for (int i = 0; i < 3; i++) {
        if (a[0][i] < a[1][i])
            r[1]++;
        else if (a[1][i] < a[0][i])
            r[0]++;
    }

    cout << r[0] << " " << r[1] << endl;
}
