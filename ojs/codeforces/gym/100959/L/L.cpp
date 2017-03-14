#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 5e3+7;

int memo[N][N][2];
int n, m;
char str[2][N];

int pd (int i, int j, bool b) {
    if (j == m)
        return (i == n);
    
    int & me = memo[i][j][b];
    if (me != -1) return me;

    me = 0;
    if (i < n && str[0][i] == str[1][j])
        if (pd(i+1, j+1, 0))
            me = 1;
    if (str[0][i-1] != str[1][j] || b)
        if (pd(i, j+1, 1))
            me = 1;
    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf(" %s %s", str[0], str[1]);
    n = strlen(str[0]);
    m = strlen(str[1]);
    if (str[0][0] == str[1][0] && pd(1, 1, 0))
        printf("Yes\n");
    else
        printf("No\n");
}
