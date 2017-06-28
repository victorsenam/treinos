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


const int N = 1e3;
int n, m;

int adj[30][30];
char str[2][N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 30; i++)
        adj[i][i] = 1;

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char a, b;
        cin >> a >> b;

        adj[a-'a'][b-'a'] = 1;
    }

    for (int k = 0; k < 30; k++)
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 30; j++)
                adj[i][j] |= (adj[i][k] & adj[k][j]);

    for (int i = 0; i < m; i++) {
        cin >> str[0] >> str[1];

        bool ok = (strlen(str[0]) == strlen(str[1]));
        for (int j = 0; ok && str[0][j]; j++)
            ok &= (adj[str[0][j]-'a'][str[1][j]-'a']);
        if (ok)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}
