#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 200;
const int K = 13;
const int M = (1<<11);

char memo[M][M];
int visi[M][M], turn;
char it[N][K];
int n, m;

string prt (int ms) {
    return bitset<K>(ms).to_string();
}

char pd (int wh, int an) {
    char & me = memo[wh][an];
    if (visi[wh][an] == turn) return me;
    visi[wh][an] = turn;

    me = K;
    int cnt = 0;
    int ms;
    int j;
    for (int i = 0; i < n && cnt <= 1; i++) {
        ms = 1;
        for (j = 0; j < m; j++, (ms<<=1)) {
            if (!(wh&ms)) continue;
            if (!!(an&ms) != (it[i][j]-'0')) break;
        }
        cnt += (j == m);
    }

    if (cnt <= 1) {
        //DEBUG("(%s,%s) defined\n", prt(wh).c_str(), prt(an).c_str());
        me = 0;
    } else {
        ms = 1;
        for (j = 0; j < m; j++, (ms<<=1)) {
            if (wh&ms) continue;
            char loc = max(pd((wh|ms), an), pd((wh|ms), (an|ms)))+1;
            me = min(me, loc);
            //if (me == loc) DEBUG("(%s,%s) add %d\n", prt(wh).c_str(), prt(an).c_str(), j);
        }
    }

    return me;
}

int main () {
    while (scanf("%d %d", &m, &n) != EOF && (n || m)) {
        turn++;
        for (int i = 0; i < n; i++)
            scanf(" %s", it[i]);

        printf("%d\n", pd(0, 0));
    }
}
