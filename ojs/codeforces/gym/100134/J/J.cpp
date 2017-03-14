#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 15007;

int t;
int vs[N], tr;
int q[6];
int p;

bool move (int k) {
    printf("%d ", p);
    q[abs(k)]--;
    p += k;
    return 1;
}

int main () {
    freopen("jumping.in", "r", stdin);
    freopen("jumping.out", "w", stdout);
    scanf("%d", &t);

    while (t--) {
        tr++;
        p = 0;

        for (int i = 1; i <= 3; i++)
            scanf("%d", &q[i]);

        int c = q[3];
        if (q[3]%3 == 0) {
            for (int i = 0; i < c/3; i++)
                move(3);
            move(1);
            for (int i = 0; i < c/3; i++)
                move(-3);
            move(1);
            for (int i = 0; i < c/3; i++)
                move(3);
        } else if (q[3]%3 == 1) {
            for (int i = 0; i <= c/3; i++)
                move(3);
            move(-2);
            for (int i = 0; i < c/3; i++)
                move(-3);
            move(1);
            for (int i = 0; i < c/3; i++)
                move(3);
            move(2);
        } else {
            for (int i = 0; i <= c/3; i++)
                move(3);
            move(-1);
            for (int i = 0; i < c/3; i++)
                move(-3);
            move(-1);
            for (int i = 0; i <= c/3; i++)
                move(3);
        }

        while (q[1] > 1)
            move(1);

        int b = q[2];
        if (q[2]%2 == 0) {
            for (int i = 0; i < b/2; i++)
                move(2);
            move(1);
            for (int i = 0; i < b/2; i++)
                move(-2);
        } else {
            for (int i = 0; i <= b/2; i++)
                move(2);
            move(-1);
            for (int i = 0; i < b/2; i++)
                move(-2);
        }

        printf("%d\n", p);
    }
}
