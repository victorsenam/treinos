#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int n;
char str[N];
bool visi[N][3][2];
int memo[N][3][2];

int pd(int i, int s, bool t) {
    if (s == 3)
        return -n;
    if (i == n) {
        if (s == 0)
            return -n;
        else
            return 0;
    }

    if (visi[i][s][t])
        return memo[i][s][t];
    visi[i][s][t] = 1;

    int & me = memo[i][s][t];

    me = pd(i+1, s, t);
    bool mt = (str[i]-'0' == t);
    if (s == 1)
        mt = !mt;

    if (mt)
        me = max(me, mt + pd(i+1, s, !t));
    else
        me = max(me, !mt + pd(i+1, s+1, !t));

    return me;
}


int main () {

    scanf("%d", &n);

    scanf(" %s", str);

    printf("%d\n", max(pd(0, 0, 0), pd(0, 0, 1)));
}
