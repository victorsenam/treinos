#include <bits/stdc++.h>

using namespace std;

#define N 200000

int ma[2], n, a, t;
set<long long int> c[2], d[2];
int dis[2][N+1];
set<long long int>::iterator mt, at, bt;
char x;

int main () {
    scanf("%d %d %d", &ma[1], &ma[0], &n);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < ma[i]; j++) {
            dis[i][j] = 0;
        }
        c[i].insert(0);
        c[i].insert(ma[i]);
        d[i].insert(ma[i]);

        dis[i][ma[i]] = 1;
    }

    for (int i = 0 ; i < n ; i++) {
        scanf(" %c %d", &x, &a);
        if (x == 'H') t = 0;
        else t = 1;

        mt = c[t].insert(a).first;
        at = bt = mt;
        at--;
        bt++;

        if (dis[t][*bt - *at]) {
            dis[t][*bt - *at]--;
            if (!dis[t][*bt - *at]) {
                d[t].erase(*bt - *at);
            }
        }

        if (!dis[t][*bt - *mt]) d[t].insert(*bt - *mt);
        dis[t][*bt - *mt]++;

        if (!dis[t][*mt - *at]) d[t].insert(*mt - *at);
        dis[t][*mt - *at]++;

        printf("%I64d\n", *(d[0].rbegin()) * *(d[1].rbegin()));
    }

}
