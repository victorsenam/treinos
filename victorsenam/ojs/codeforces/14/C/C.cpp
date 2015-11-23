#include <bits/stdc++.h>

using namespace std;

int x[4][2], y[4][2];
int mask;
multiset<pair<int, bool> > gx, gy;
set<int> sx, sy;
set<int>::iterator it;

void fail( ){
    printf("NO\n");
    exit(0);
}

int main () {
    for (int i = 0; i < 4; i++) {
        scanf("%d %d %d %d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);

        if (x[i][0] > x[i][1])
            swap(x[i][0], x[i][1]);
        if (y[i][0] > y[i][1])
            swap(y[i][0], y[i][1]);

        if (x[i][0] == x[i][1] && y[i][0] == y[i][1])
            fail();
        if (x[i][0] != x[i][1] && y[i][0] != y[i][1])
            fail();

        if (x[i][0] == x[i][1]) {
            sx.insert(x[i][0]);
            gx.insert(make_pair(x[i][0], 0));

            sy.insert(y[i][0]);
            gy.insert(make_pair(y[i][0], 1));

            sy.insert(y[i][1]);
            gy.insert(make_pair(y[i][1], 1));
        }
        if (y[i][0] == y[i][1]) {
            sy.insert(y[i][0]);
            gy.insert(make_pair(y[i][0], 0));

            sx.insert(x[i][0]);
            gx.insert(make_pair(x[i][0], 1));

            sx.insert(x[i][1]);
            gx.insert(make_pair(x[i][1], 1));
        }
    }
    if (sx.size() != 2 || sy.size() != 2)
        fail();

    for (it = sx.begin(); it != sx.end(); ++it) {
        if (gx.count(make_pair(*it, 0)) != 1)
            fail();
        if (gx.count(make_pair(*it, 1)) != 2)
            fail();
    }
    
    for (it = sy.begin(); it != sy.end(); ++it) {
        if (gy.count(make_pair(*it, 0)) != 1)
            fail();
        if (gy.count(make_pair(*it, 1)) != 2)
            fail();
    }

    printf("YES\n");
}
