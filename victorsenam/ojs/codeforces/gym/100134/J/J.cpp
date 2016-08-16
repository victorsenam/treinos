#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 15007;

int t;
int a, b, c, n;
int vs[N], tr;
int q[6];
int p;
bool ch;

bool move (int k) {
    if (vs[p + k] == tr) return 0;
    if(p + k < 0 || p + k > n) return 0;
    if(q[abs(k)]-- <= 0) return 0;
    ch = 0;
    printf("%d ", p);
    vs[p] = tr;
    p += k;
    return 1;
}

int main () {
    freopen("jumping.in", "r", stdin);
    freopen("jumping.out", "w", stdout);
    scanf("%d", &t);

    while (t--) {
        tr++;

        for (int i = 1; i <= 3; i++)
            scanf("%d", &q[i]);

        while (q[3] > 3 && q[2] > 2) {
            if (q[3] <= q[2]) {
                move(2);
                move(2);
                move(-3);
                move(2);
                move(2);
            } else {
                move(3);
                move(-2);
                move(3);
                move(-2);
                move(3);
            }
        }
    }
}
