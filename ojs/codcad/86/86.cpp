#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int d, n;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while ((cin >> n >> d) || n || d) {
        d = n-d;
        string s;
        cin >> s;

        int p = 0;
        for (int i = 0; i < n; i++) {
            while (n - i > d - p && p && s[p - 1] < s[i])
                p--;
            s[p++] = s[i];
        }
        s.resize(d);
        cout << s << endl;
    }
}
