#include <bits/stdc++.h>

using namespace std;

const int N = 20;
const int M = (1<<10);

bool memo[N][2][M][M];
int visi[N][2][M][M];
int res[N][2][M][M];
char str[N];
char in[N];
int turn;
long long ans;
int n;

bool pd (int i, bool pre, int one, int two) {
    if (i == n)
        return 1;

    bool & me = memo[i][pre][one][two];
    int & re = res[i][pre][one][two];
    if (visi[i][pre][one][two] == turn)
        return me;
    visi[i][pre][one][two] = turn;

    int top = 9;
    if (pre)
        top = str[i];       

    me = 0;
    while (top >= 0 && !me) {
        if (one&(1<<(top))) {
            if (two&(1<<(top)));
            else if (pd(i+1, pre&&(top>=str[i]), one, (two|(1<<top))) ) {
                me = 1;
                re = top;
            }
        } else {
            if (pd(i+1, pre&&(top>=str[i]), (one|(1<<top)), two) ) {
                me = 1;
                re = top;
            }
        }
        top--;
    }

    return me;
}

void mount (int i, bool pre, int one, int two) {
    if (i == n)
        return;

    int re = res[i][pre][one][two];
    ans *= 10;
    ans += re;

    int no = (one|(1<<re));
    int nt = two;
    if (one&(1<<re))
        nt |= (1<<re);

    mount(i+1, pre&&(re>=str[i]), no, nt);
}

int main () {
    while (scanf(" %s", str) != EOF) {
        turn++;
        for (n = 0; str[n]; n++) str[n] -= '0';
        pd(0, 1, 0, 0);
        ans = 0;
        mount(0, 1, 0, 0);
        printf("%lld\n", ans);
    }
}
