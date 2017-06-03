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
typedef unsigned long long int ui;

const int N = 2e6+7;
const int B = 6;

int n, q;
ui a[N];
int qr[N][2];
int nx[N][34];
int bd[N][34];
int v[N];

bool testa (int i, int j) {
    if (j > n) return 0;
    ui acc = a[i];

    for (int k = i+1; k < j; k++) {
        if (acc > (acc^a[k]))
            return 0;
        acc ^= a[k];
    }
    
    return 1;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int j = 0; j < B; j++) {
        bd[n][j] = nx[n][j] = n;
        for (int i = n-1; i >= 0; i--) {
            nx[i][j] = nx[i+1][j];
            if (a[i]&(1u<<j))
                nx[i][j] = i;

            if (!j) {
                if (nx[i][j] == n)
                    bd[i][j] = n;
                else
                    bd[i][j] = nx[nx[i][j]+1][j];
            } else {
                if (bd[i][j-1] < nx[i][j])
                    bd[i][j] = bd[i][j-1];
                else if (nx[i][j] == n)
                    bd[i][j] = n;
                else {
                    int k = nx[i][j];
                    bd[i][j] = min(nx[k+1][j], bd[k][j-1]);

                    if (nx[i][j-1] <= k) {
                        bd[i][j] = min(bd[i][j], nx[k+1][j-1]);
                    }
                }
            }

            if (j && bd[i][j-1] < nx[i][j]) 
                bd[i][j] = bd[i][j-1];
            else if (nx[i][j] == n)
                bd[i][j] = n;
            else
                bd[i][j] = nx[nx[i][j]+1][j];
            

            v[i] = bd[i][j];
        }
        cout << j << " : ";
        for (int i = 0; i <= n; i++)
            cout << nx[i][j] << " ";
        cout << " | ";
        for (int i = 0; i <= n; i++)
            cout << bd[i][j] << " ";
        cout << endl;

    }

    for (int i = 0; i < n; i++) {
        if (!testa(i, v[i]))
            cout << "nao e [" << i << "," << v[i] << ")" << endl;
        if (testa(i, v[i]+1))
            cout << "e [" << i << "," << v[i]+1 << ")" << endl;
        assert(testa(i, v[i]));
        assert(!testa(i, v[i]+1));
        cout << v[i] << " ";
    }
    cout << endl;
}
