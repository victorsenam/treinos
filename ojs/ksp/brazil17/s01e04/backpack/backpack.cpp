#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = (1<<24);
int n, m;

int v[25];
int w[101];

ll acc[N];
bitset<N> b[3];
int visi[2][N], memo[2][N], turn, f[N];

void printa (int j) {
    cout << bitset<4>(j);
}

int get (int id, int pos, int mask) {
    if (pos == n)
        return (b[id][mask]);
    
    if (visi[pos&1][mask] >= turn - 1)
        return memo[pos&1][mask];
    visi[pos&1][mask] = turn;

    memo[pos&1][mask] = get(id, pos+1, mask);
    if (mask&(1<<pos));
        memo[pos&1][mask] += get(id, pos+1, mask^(1<<pos));
    return memo[pos&1][mask];
}

int get2 (int pos, int mask) {
    if (pos == n) {
        if (__builtin_popcount(mask) & 1)
            return f[mask];
        else
            return -f[mask];
    }
    if (visi[pos&1][mask] >= turn - 1)
        return memo[pos&1][mask];
    visi[pos&1][mask] = turn;

    memo[pos&1][mask] = get2(pos+1,mask);
    if (mask&(1<<pos))
        memo[pos&1][mask] += get2(pos+1,mask^(1<<pos));
    return memo[pos&1][mask];
}

int main () {
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> v[i];
    for (int i = 0; i < m; i++)
        cin >> w[i];

    for (int i = 0; i < (1<<n); i++) {
        for (int j = 0; j < n; j++)
            if (i&(1<<j))
                acc[i] += v[j];
    }

    sort(w, w+m, [] (int i, int j) {
        return w[i] > w[j];
    });
    m = min(n,m);

    b[1][0] = 1;

    for (int i = 0; i < m; i++) {
        cout << "mala " << i << endl;
        for (int j = 0; j < (1<<n); j++) {
            b[0][j] = (acc[j] <= ll(w[i]));
            if (b[0][j]) {
                printa(j);
                cout << endl;
            }
        }

        turn += 2;
        for (int i = n-1; i >= 0; i--) {
            turn++;
            for (int j = 0; j < (1<<n); j++)
                get(0,i,j);
        }
        for (int j = 0; j < (1<<n); j++)
            f[j] = get(0,0,j);

        turn += 2;
        for (int i = n-1; i >= 0; i--) {
            turn++;
            for (int j = 0; j < (1<<n); j++)
                get(1,i,j);
        }
        for (int j = 0; j < (1<<n); j++)
            f[j] *= get(1,0,j);

        turn += 2;
        for (int i = n-1; i >= 0; i--) {
            turn++;
            for (int j = 0; j < (1<<n); j++)
                get2(i,j);
        }

        cout << "juntando " << endl;
        for (int j = 0; j < (1<<n); j++) {
            b[1][j] = get2(0,j);
            if (b[1][j]) {
                printa(j);
                cout << endl;
            }
        }

        if (b[1][(1<<n)-1]) {
            cout << i+1 << endl;
            return 0;
        }
    }
    cout << "NIE" << endl;
}
