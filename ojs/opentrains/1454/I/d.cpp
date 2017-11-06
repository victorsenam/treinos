#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define seta(a, b) memset(a, b, sizeof(a))
#define forn(i, n) for (int i = 0; i < (int) n; ++i)

const int TMAX = 5;
const int LEVELMAX = 10 + 1;
const int LMAX = 70 + 1;

int n, t, lvl;
int len[TMAX], cnt[TMAX];
int may[2][LMAX][LMAX][LMAX][LEVELMAX];
unsigned char used[2][LMAX][LMAX][LMAX][LEVELMAX];

void move(int i0, int i1, int i2, int i3, int x) {
    if (may[i0 & 1][i1][i2][i3][x] == 0 && used[i0 & 1][i1][i2][i3][x + 1] > used[i0 & 1][i1][i2][i3][x]) {
        may[i0 & 1][i1][i2][i3][x + 1] = lvl;
        used[i0 & 1][i1][i2][i3][x + 1] = used[i0 & 1][i1][i2][i3][x];
        return;
    }
    int maybe = may[i0 & 1][i1][i2][i3][x];
    unsigned char count = used[i0 & 1][i1][i2][i3][x];
    // 0
    if (i0 < cnt[0] && maybe >= len[0] && used[(i0 + 1) & 1][i1][i2][i3][x] > count) {
        used[(i0 + 1) & 1][i1][i2][i3][x] = count;
        may[(i0 + 1) & 1][i1][i2][i3][x] = maybe - len[0];
    }
    // 1
    if (i1 < cnt[1] && maybe >= len[1] && used[i0 & 1][i1 + 1][i2][i3][x] > count) {
        used[i0 & 1][i1 + 1][i2][i3][x] = count;
        may[i0 & 1][i1 + 1][i2][i3][x] = maybe - len[1];
    }
    // 2
    if (i2 < cnt[2] && maybe >= len[2] && used[i0 & 1][i1][i2 + 1][i3][x] > count) {
        used[i0 & 1][i1][i2 + 1][i3][x] = count;
        may[i0 & 1][i1][i2 + 1][i3][x] = maybe - len[2];
    }
    // 3
    if (i3 < cnt[3] && maybe >= len[3] && used[i0 & 1][i1][i2][i3 + 1][x] > count) {
        used[i0 & 1][i1][i2][i3 + 1][x] = count;
        may[i0 & 1][i1][i2][i3 + 1][x] = maybe - len[3];
    }
    // 4
    int need = maybe / len[4];
    if (maybe == need * len[4] && count + need <= cnt[4] && used[i0 & 1][i1][i2][i3][x + 1] > count + need) {
        used[i0 & 1][i1][i2][i3][x + 1] = count + need;
        may[i0 & 1][i1][i2][i3][x + 1] = lvl;
    }
}

void solve() {
    seta(used[0], 255);
    used[0][0][0][0][0] = 0;
    may[0][0][0][0][0] = lvl;
    int xdelta = (n - 1) / t + 1;
    forn(i0, cnt[0] + 1) {
        seta(used[(i0 & 1) ^ 1], 255);
        forn(i1, cnt[1] + 1)
            forn(i2, cnt[2] + 1)
                forn(i3, cnt[3] + 1) {
                    if (i0 * len[0] * 3 < i1 * len[1] + i2 * len[2] + i3 * len[3]) continue;

                    int xmin = max(0, (i0 * len[0] + i1 * len[1] + i2 * len[2] + i3 * len[3]) / lvl);
                    int xmax = min(n - 1, xmin + xdelta);
                    if (xmin > 0) xmin--;

                    for (int x = xmin; x <= xmax; ++x)
                        if (used[i0 & 1][i1][i2][i3][x] <= cnt[4])
                            move(i0, i1, i2, i3, x);
                }
    }
    if (used[cnt[0] & 1][cnt[1]][cnt[2]][cnt[3]][n] <= cnt[4])
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}

int main () {
    freopen("dirichlet.in", "r", stdin);
    freopen("dirichlet.out", "w", stdout);
    while (scanf("%d%d", &t, &n) > 0) {
        int sum = 0;
        vector< pair<int, pair<int, int> > > order;
        forn(i, t) {
            int len, cnt;
            scanf("%d%d", &cnt, &len);
            sum += cnt * len;
            order.push_back(make_pair(cnt * len, make_pair(cnt, len)));
        }

        if (sum % n != 0) {
            cout << "No" << endl;
            continue;
        }

        sort(order.begin(), order.end());
        reverse(order.begin(), order.end());
        forn(i, order.size()) {
            cnt[i] = order[i].second.first;
            len[i] = order[i].second.second;
        }
        while (t < TMAX) {
            cnt[t] = 0;
            len[t] = 1;
            t++;
        }

        lvl = sum / n;
        solve();
    }
    return 0;
}
