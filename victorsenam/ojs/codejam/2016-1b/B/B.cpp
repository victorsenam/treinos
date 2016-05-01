#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 20;
const ll V = 1e17;

int ts;
char str[2][N];
int st;

ll memo[N][3];
char res[N][3][2];
char prn[2][N];
int visi[N][3], turn;

ll pd (int i, int st) {
    if (!str[0][i]) return 0;
    ll & me = memo[i][st];
    if (visi[i][st] == turn)
        return me;
    visi[i][st] = turn;

    me = V*10;
    ll loc;
    int a[2];

    for (a[0] = '0'; a[0] <= '9'; a[0]++) {
        if (str[0][i] != '?' && str[0][i] != a[0]) continue;
        for (a[1] = '0'; a[1] <= '9'; a[1]++) {
            if (str[1][i] != '?' && str[1][i] != a[1]) continue;
    
            if (st == 2) {
                loc = pd(i+1, (a[0]<=a[1])+(a[0]==a[1]) )/10 + V*abs(a[1]-a[0]);
            } else {
                loc = pd(i+1, st)/10 + V*(a[st]-a[!st]);
            }

            if (loc < me) {
                me = loc;
                res[i][st][0] = a[0];
                res[i][st][1] = a[1];
            }
        }
    }
    return me;
}

int main () {
    scanf("%d", &ts);
    for (int tt = 1; tt <= ts; tt++) {
        ++turn;
        scanf(" %s %s", str[0], str[1]);

        pd(0,2);
        
        int st = 2;
        int i;
        for (i = 0; str[0][i]; i++) {
            for (int k = 0; k < 2; k++)
                prn[k][i] = res[i][st][k];

            if (st == 2)
                st = (res[i][st][0] <= res[i][st][1]) + (res[i][st][0] == res[i][st][1]);
        }
        prn[0][i] = prn[1][i] = 0;

        printf("Case #%d: %s %s\n", tt, prn[0], prn[1]);
    }
}
