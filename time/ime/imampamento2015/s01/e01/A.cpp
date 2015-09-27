#include <bits/stdc++.h>

using namespace std;

int main () {
    int n, a, bal, t;

    t = 0;

    while(scanf("%d", &n) != EOF && n) {
        bal = 0;
        while (n--) {
            scanf("%d", &a);
            if (a == 0) bal--;
            else bal++;
        }
        printf("Case %d: %d\n", ++t, bal);
    }
}
