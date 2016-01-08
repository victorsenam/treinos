// BEM ERRADO... Talvez a ideia esteja certa mas o codigo esta bem errado...

#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

const int N = 5000;

char s[N], t[N];
bool visi[N][N][2][2];
int memo[N][N][2][2];
int n, m;

int pd (int i, int j, bool op, bool re) {
    if (i == n)
        return 0;
    if (j == m) {
        if (op) {
            return pd(i, 0, 0, 0);
        } else if (re) {
            return n+10;
        } else
            return pd(i, 0, 0, 1);
    }

    int & me = memo[i][j][op][re];

    if (visi[i][j][op][re])
        return me;
    visi[i][j][op][re] = 1;

    int k = j;
    if (re)
        k = m-j-1;

    if (op) {
        me = pd(i, 0, 0, 0);

        if (s[i] == t[k])
            me = min(me, pd(i+1, j+1, 1, re));
    } else {
        me = pd(i, j+1, 0, re);

        if (s[i] == t[k])
            me = min(me, pd(i+1, j+1, 1, re) + 1);
    }
    return me;
}

int main () {
    scanf(" %s %s", t, s);
    n = strlen(s);
    m = strlen(t);

    int res = pd(0, 0, 0, 0);
    
}
