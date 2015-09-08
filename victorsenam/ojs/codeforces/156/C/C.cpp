#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 107;
const int D = 28;
const num MOD = 1000000007ll;

num memo[N][2*D];
int vis[N][2*D];
int turn;
int t;
char tmp[N];
int str[N];
int n;

num pd (int i, int d) {
    if (d < 0 || d > 26)
        return 0;
    if (i == n-1) {
        return (str[i] - 26 + d >= 0 && str[i] - 26 + d <= (int)('z'-'a'));
    }

    printf("%c", str[i]-26+d+'a');

    num & me = memo[i][d];
    if (vis[i][d] == turn)
        return me;

    vis[i][d] = turn;

    me = 0;
    for (int j = -(str[i] - 26 + d); str[i]-26+d+j <= (int)('z'-'a'); j++) {
        me = (me + pd(i+1, 26-j))%MOD;
    }
    
    return me;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf(" %s", tmp);
        for (n = 0; tmp[n] != '\0'; n++)
            str[n] = tmp[n]-'a';
        turn++;
        printf("%d\n", (int)pd(0, 26)-1);
    }
}
