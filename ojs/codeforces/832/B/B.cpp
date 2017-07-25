#include <bits/stdc++.h>
#define debug if (0)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

bool gd[N];
char str[N];
char qry[N];
int n;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> str;
    for (int i = 0; str[i]; i++)
        gd[str[i]] = 1;

    cin >> str;
    int l = strlen(str);

    cin >> n;

    while (n--) {
        cin >> qry;
        int s = strlen(qry);

        int j = 0;
        bool ok = 1;
        for (int i = 0; ok && str[i]; i++) {
            if (str[i] == '*') {
                while (l - i <= s - j) {
                    debug cout << l - i << " ? " << s - j << endl;
                    debug cout << "ignore " << qry[j] << endl;
                    ok &= !gd[qry[j++]];
                }
                debug cout << l - i << " ? " << s - j << endl;
            } else if (!qry[j]) {
                debug cout << "fail" << endl;
                ok = 0;
            } else if (str[i] == '?') {
                debug cout << "? with " << qry[j] << endl;
                ok &= gd[qry[j++]];
            } else {
                debug cout << str[i] << " with " << qry[j] << endl;
                ok &= (str[i] == qry[j++]);
            }
        }

        ok &= (!qry[j]);

        if (ok)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
