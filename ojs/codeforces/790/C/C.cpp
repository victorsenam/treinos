#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 80;
const int K = 26;

int memo[N*8][K][K];
int n;
char str[N];

int pd (int u, int i, int j, int l, int r) {
    if (i == j) {
        if (l == r && str[i] - 'A' == l) {
            //printf("%c[%d,%d]%c\n", l+'A', i, j, r+'A');
            return 0;
        } else {
            return 1e8;
        }
    }
    if (i + 1 == j) {
        if (l + 'A' == 'V' && r + 'A' == 'K')
            return 1e8;
        if (l == str[i] - 'A' && r == str[j] - 'A')
            return 0;
        if (r == str[i] - 'A' && l == str[j] - 'A')
            return 1;
        return 1e8;
    }

    int & me = memo[u][l][r];
    if (me != -1)
        return me;
    me = 1e8;

    for (int a = 0; a < 26; a++) {
        for (int b = 0; b < 26; b++) {
            if (a + 'A' == 'V' && b + 'A' == 'K') continue;
            
            me = min(me, pd(u*2, i, (i+j)/2, l, a) + pd(u*2+1, (i+j)/2+1, j, b, r));
            me = min(me, pd(u*2, i, (i+j)/2, l, b) + pd(u*2+1, (i+j)/2+1, j, a, r) + 1);
        }
    }

    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf("%d", &n);
    scanf("%s", str);

    int res = 1e8;
    for (int a = 0; a < 26; a++)
        for (int b = 0; b < 26; b++)
            res = min(res, pd(1, 0, n-1, a, b));
    printf("%d\n", res);
}
