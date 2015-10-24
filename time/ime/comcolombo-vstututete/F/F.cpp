#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int t;
int n;
int a[N], b[N], c[N];
set<int> got;
set<int>::iterator it;
set<pair<int, int> > ev;
set<pair<int, int> >::iterator jt;
pair<int, int> aux;
int proc[N];
int turn;

int main(  ) {
    scanf("%d", &t);

    int ts = 0;
    while (t--) {
        scanf("%d", &n);

        got.clear();
        ev.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", a+i, b+i, c+i);

            got.insert(a[i]);
        }
        int res = got.size();

        for (int i = 0; i < n; i++) {
            it = got.lower_bound(b[i]);
            bool ok = 0;
            while (!ok) {
                if (it == got.end() || *it > c[i])
                    break;
                if (*it != a[i]) {
                    ok = 1;
                }
                it++;
            }

            if (!ok) {
                ev.insert(make_pair(b[i], -i));
            }
        }

        turn++;
        for (jt = ev.begin(); jt != ev.end(); ++jt) {
            if (jt->second > 0) {
                if (jt->second < res)
                    continue;
                res++;
            } else {
                ev.insert(make_pair(c[-jt->second], res));
            }
        }
        printf("Case #%d: %d\n", ++ts, res);
    }
}
