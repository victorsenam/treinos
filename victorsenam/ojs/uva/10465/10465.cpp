#include <bits/stdc++.h>
#define MAX 10001

int m, n, t, s, ms, mt;

int memo[MAX][2]; // saves the final state for [0] -> time left && [1] -> burgers eaten

void eat (int s, int g, int l) {
    int a, b, r;
    if (memo[l][1] != -1 || l < 0) return;

    if (l == 0) {
        memo[0][0] = 0;
        memo[0][1] = 0;
        return;
    }

    a = l-s;
    b = l-g;
    if (b >= 0) {
        eat(s,g,a);
        eat(s,g,b);

        if (memo[a][0] < memo[b][0]) r = a;
        else if (memo[a][0] > memo[b][0]) r = b;
        else if (memo[a][1] > memo[b][1]) r = a;
        else r = b;
    } else if (a >= 0) {
        eat(s,g,a);
        r = a;
    } else {
        r = -1;
    }

    if (r < 0) {
        memo[l][0] = l;
        memo[l][1] = 0;
    } else {
        memo[l][0] = memo[r][0];
        memo[l][1] = memo[r][1] + 1;
    }
}

int main () {
    while (scanf("%d %d %d", &m, &n, &t) != EOF && m && n && t) {
        for (int i = 0; i <= t; i++) {
            memo[i][0] = t;
            memo[i][1] = -1;
        }

        eat(std::min(m,n), std::max(m,n), t);
        
        printf("%d", memo[t][1]);
        if (memo[t][0]) printf(" %d", memo[t][0]);
        printf("\n");
    }
}
