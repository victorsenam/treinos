#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+2;

int qt[N][2];
char str[2][N];

int ts;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> ts;

    while (ts--) {
        for (int i = 'a'; i <= 'z'; i++)
            qt[i][0] = qt[i][1] = 0;
        cin >> str[0] >> str[1];
        for (int j = 0; j < 2; j++) {
            for (int i = 0; str[j][i]; i++) {
                qt[str[j][i]][j]++;
            }
        }

        int ha = 0, hb = 0, hax2 = 0;

        for (int i = 'a'; i <= 'z'; i++) {
            if (qt[i][0] && !qt[i][1])
                ha = 1;
            if (qt[i][1] && !qt[i][0])
                hb = 1;
            if (qt[i][0] > 1 && !qt[i][1])
                hax2 = 1;
        }

        char r = 'B';
        if (ha && (!hb || hax2))
            r = 'A';
        cout << r << endl;
    }
}
