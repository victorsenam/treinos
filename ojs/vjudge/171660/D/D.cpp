#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii,pii> rrr;
#define pb push_back

const int N = 30;

int n, m;

struct pos {
    int i, j;

    pos (int a, int b) : i(a), j(b) {}
    pos () : i(-1), j(-1) {}

    bool isvalid () {
        if (i < 0 || i >= n || j < 0 || j >= m) return 0;
        return 1;
    }

    bool operator < (const pos & ot) const {
        if (i != ot.i) return i < ot.i;
        return j < ot.j;
    }

    pos get (int d, int k) {
        pos res;
        if (!isvalid())
            return pos(-1,-1);
        if (k == 0) {
            if (i < d)
                return pos(-1,-1);
            if (i == d) // ajeitar print aq
                return pos(-1,0);
            res = pos(d + d - i + 1, j);
        } else if (k == 1) {
            if (j < d)
                return pos(-1,-1);
            if (j == d) // ajeitar print aq
                return pos(-1,0);
            res = pos(i, d + d - j + 1);
        } else if (k == 2) {
            if (j - i < d)
                return pos(-1,-1);
            if (j - i == d)
                return pos(-1,0);
            res = pos(j-d,i+d);
        } else {
            if (i + j < d)
                return pos(-1,-1);
            if (i + j == d)
                return pos(-1,0);
            res = pos(d-j,d-i);
        }
        if (!res.isvalid())
            return pos(-1,-1);
        return res;
    }
};
ostream & operator << (ostream & os, pos r) {
    return os << "(" << r.i << "," << r.j << ")";
}

char mat[N][N];

int main () {
    while (cin >> n >> m) {
        int cn = 0;
        for (int i = 0; i < n; i++) {
            cin >> mat[i];
            for (int j = 0; j < m; j++) {
                cn += (mat[i][j] == '.');
            }
        }

        pair<pos,pos> res(pos(N,N),pos(N,N));

        for (int k = 0; k < 4; k++) {
            for (int d = -n-m; d <= n+m; d++) {
                pos cur;
                pos mn(N,N), mx(-N,-N);
                int cc = 0;

                for (cur.i = 0; cc != -1 && cur.i < n; cur.i++) {
                    for (cur.j = 0; cc != -1 && cur.j < m; cur.j++) {
                        pos rev = cur.get(d,k);

                        if (rev.i == -1) {
                            if (rev.j == 0) {
                                mn = min(mn, cur);
                                mx = max(mx, cur);
                            }
                        } else if (mat[cur.i][cur.j] == mat[rev.i][rev.j]) {
                            cc = -1;
                        } else {
                            cc++;
                        }
                    }
                }

                if (cc == cn) {
                    if (mn.j > mx.j)
                        swap(mn, mx);
                    res = min(res, pair<pos,pos>(mn,mx));                   
                }
            }
        }

        cout << res.first.i+1 << " " << res.first.j+1 << " " << res.second.i+1 << " " << res.second.j+1 << endl;
    }
}
