#include <bits/stdc++.h>

using namespace std;

const int N = 200007;

int dest, cap, n, m;
int gs[3][N];
int cn[3];
int t;
int pos, fuel;

int main () { 
    scanf("%d %d %d %d", &dest, &cap, &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &t);
        t--;
        scanf("%d", &gs[t][cn[t]++]);
    }

    for (int i = 0; i < 3; i++)
        sort(gs[t], gs[t]+cn[t]);

    for (int i = 0; i < m; i++) {
        scanf("%d", &pos);
        fuel = cap;
        int ty = 2;
        int r, m;
        r = m = 0;
        while (pos != s) {
            if (abs(s-pos) <= fuel) {
                pos = s;
            } else if (s < pos) {
                for (int k = 2; k >= 0; k--) {
                    int lo = lower_bound(gs[k], gs[k]+cn[k], pos) - gs[k] - 1;
                    if (lo < 0)
                        continue;
                    
                    if (
                }
            } else {
            }
        }
    }
}
