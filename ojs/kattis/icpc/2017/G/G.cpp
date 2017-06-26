#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug if(true)
#else
#define debug if(false)
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e2+3;

struct mtx {
    int n, m;
    int v[N][N];

    mtx () {}
    mtx (mtx & o) {
        n = o.n; m = o.m;
        for (int i = 0; i < n; i++)
            for (int j =0 ; j< m; j++)
                v[i][j] = o.v[i][j];
    }

    void transpose () {
        int k = max(n,m);
        swap(n,m);
        for (int i = 0; i < k; i++)
            for (int j = i+1; j < k; j++)
                swap(v[i][j], v[j][i]);
    }

    void tip () {
        for (int i = 0; n - i - 1 > i; i++)
            for (int j = 0; j < m; j++)
                swap(v[i][j], v[n-i-1][j]);
    }

    bool getcol (int i, int j) {
        bool c = 0;
        for (int mi = -1; mi <= 1; mi++) {
            if (i + mi < 0 || i + mi >= n) continue;
            for (int mj = -1; mj <= 1; mj++) {
                if (j + mj < 0 || j + mj >= m) continue;
                c ^= v[i+mi][j+mj];
            }
        }
        return c;
    }

    int buildfrom (mtx & x) {
        n = x.n; m = x.m;
        for (int i = 0; i < m; i++)
            v[0][i] = 0;
        for (int i = 1; i < n; i++) {
            v[i][0] = 0;
            for (int j = 1; j < m; j++) {
                v[i][j] = 0;
                v[i][j] = (getcol(i-1, j-1) != x.v[i-1][j-1]);
                if ((i == n-1 || j == m-1) && v[i][j])
                    return i-1;
            }
            if (getcol(i-1,m-1) != x.v[i-1][m-1])
                return i-1;
        }
        for (int i = 0; i < m; i++)
            if (getcol(n-1,i) != x.v[n-1][i])
                return n-1;
        return -1;
    }

    void resz () {
        int r,c;
        for (r = 0; r < n; r++) {
            bool k = 0;
            for (int j = 0; !k && j < m; j++)
                k |= v[r][j];
            if (k) break;
        }
        for (c = 0; c < m; c++) {
            bool k = 0;
            for (int i = 0; !k && i < n; i++)
                k |= v[i][c];
            if (k) break;
        }
        n -= r; m -= c;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                v[i][j] = v[i+r][j+c];
        while (n) {
            bool k = 0;
            for (int j = 0; !k && j < m; j++)
                k |= v[n-1][j];
            if (k) break;
            n--;
        }
        while (m) {
            bool k = 0;
            for (int i = 0; !k && i < n; i++)
                k |= v[i][m-1];
            if (k) break;
            m--;
        }
    }

    void print () {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << (v[i][j] ? '#' : '.');
            cout << endl;
        }
    }
};

mtx x,a,b,c,d;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> x.m >> x.n;
    for (int i = 0; i < x.n; i++) {
        for (int j = 0; j < x.m; j++) {
            char c;
            cin >> c;
            x.v[i][j] = (c == '#');
        }
    }

    while (x.n > 2 && x.m > 2) {
        debug {
            x.print();
            cout << endl;
        }
        int row[2], col[2];
        row[0] = a.buildfrom(x);
        x.transpose();
        col[0] = c.buildfrom(x);
        x.transpose();

        if (row[0] != -1) {
            assert(col[0] != -1);
            x.v[row[0]][col[0]] ^= 1;
            if (a.buildfrom(x) != -1) {
                x.v[row[0]][col[0]] ^= 1;
                break;
            }
        }

        x = a;
        x.resz();
    }

    x.print();
}
