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

const int N = 1e6+4;

int n[2];
ll day[2][N];
ll pri[2][N];
int p[2][N];
int s[2];

void print(int k, int i)
{ cout << "[" << i << "](" << day[k][p[k][i]] << "," << pri[k][p[k][i]] << ")"; }

bool isbest(int i, int j, int k, bool pr=0) {
    if (pr) {
        bool res = isbest(i,j,k,0);
        print(k, i);
        cout << " better than ";
        print(k, j);
        cout << " ? " << res << endl;
        return res;
    }
    if (k) {
        return (day[k][p[k][i]] >= day[k][p[k][j]] && pri[k][p[k][i]] >= pri[k][p[k][j]]);
    } else {
        return (day[k][p[k][i]] <= day[k][p[k][j]] && pri[k][p[k][i]] <= pri[k][p[k][j]]);
    }
}

ll calc (int j, int i)
{ return max(day[1][p[1][j]] - day[0][p[0][i]], 0ll)*max(pri[1][p[1][j]] - pri[0][p[0][i]],0ll); }

ll divc (int lo, int hi, int l, int r) {
    if (lo > hi) return 0ll;
    int mid = (lo+hi)/2;

    int x = l;
    while (x < r && pri[0][p[0][x]] >= pri[1][p[1][mid]])
        x++;

    for (int y = l+1; y <= r; y++) {
        if (day[0][p[0][y]] >= day[1][p[1][mid]])
            break;
        if (calc(mid, y) > calc(mid, x))
            x = y;
    }

/*
    print(1,mid);
    cout << " gets ";
    print(0,x);
    cout << " with " << calc(mid, x) << endl;
*/

    return max({calc(mid, x), divc(lo, mid-1, l, x), divc(mid+1, hi, x, r)});
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n[0] >> n[1];

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n[k]; i++) {
            cin >> pri[k][i] >> day[k][i];
            p[k][i] = i;
        }
        sort(p[k], p[k] + n[k], [k] (int i, int j) {
            return day[k][i] < day[k][j];
        });
    }

    for (int k = 0; k < 2; k++) {
        s[k] = 0;
        for (int i = 0; i < n[k]; i++) {
            if (s[k] && isbest(s[k]-1, i, k))
                continue;
            while (s[k] && isbest(i, s[k]-1, k))
                s[k]--;
            swap(p[k][s[k]], p[k][i]);
            s[k]++;
        }
/*
        cout << "set " << k << endl;
        for (int i = 0; i < s[k]; i++)
            cout << "day " << day[k][p[k][i]]
              << " | price " << pri[k][p[k][i]] << endl;
*/
    }

    cout << divc(0, s[1]-1, 0, s[0]-1) << endl;
}
