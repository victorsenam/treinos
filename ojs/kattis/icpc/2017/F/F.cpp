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

const int N = 550;

int d, k;
ll qt[N];
ll cst[N][N];
ll bst[N][N];

ll sq (ll x)
{ return x*x; }

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> d >> k;

    for (int i = 0; i < d; i++) {
        int a, b;
        cin >> a >> b;
        qt[a] += b;
    }

    for (int i = 0; i < N; i++) 
        for (int j = i; j < N; j++)
            for (int k = i; k <= j; k++)
                cst[i][j] += min(sq(k-i),sq(j-k))*qt[k];

    for (int j = 0; j < N; j++)
        for (int k = 0; k <= j; k++)
            bst[0][j] += sq(k-j)*qt[k];

    for (int q = 1; q <= k; q++) {
        for (int j = 0; j < N; j++) {
            bst[q][j] = 1e14;
            for (int i = 0; i < j; i++) {
                bst[q][j] = min(bst[q][j], bst[q-1][i] + cst[i][j]);
            }
        }
    }

    cout << bst[k][N-1] << endl;
}
