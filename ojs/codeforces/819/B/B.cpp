#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug if(true)
#else
#define debug if(false)
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;
int n;
int p[N];
ll ch[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    ll cst = 0;
    ll lef = 0;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        cst += abs(p[i] - i);
        if (i <= p[i]) {
            ch[p[i] - i]++;
            lef++;
            //cout << p[i] << " is left: " << p[i] - i << endl;
        } else {
            ch[p[i] - i + n]++;
            //cout << p[i] << " : " << p[i] - i + n  << endl;
        }
    }

    ll mn = cst;
    ll sh = 0;
    //cout << lef << " " << cst << endl;
    for (int i = 0; i < n-1; i++) {
        //cout << "shift " << i+1 << endl;

        lef -= ch[i];

        cst += n-1;
        cst -= lef + lef;

        cst -= abs(n-1 - p[(n-1-i)%n]);
        cst += p[(n-1-i)%n];

        lef++;

        //cout << lef << " " << cst << endl;

        if (cst < mn) {
            mn = cst;
            sh = i+1;
        }
    }

    cout << mn << " " << sh << endl;
}
