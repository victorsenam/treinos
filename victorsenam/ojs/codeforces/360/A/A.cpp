#include <bits/stdc++.h>

using namespace std;

const int N = 5003;
const int INI = 1000000000;

typedef long long int num;

int n, m;
num init[N], sum[N];
int ty, l, r;
num d;
int op[N][4];

void fail () {
    printf("NO\n");
    exit(0);
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        init[i] = INI;
        sum[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %I64d", &ty, &l, &r, &d);
        op[i][0] = ty; op[i][1] = l; op[i][2] = r; op[i][3] = d;

        l--;

        if (ty == 1) {
            for (int j = l; j < r; j++)
                sum[j] += d;
        } else {
            for (int j = l; j < r; j++) {
                init[j] = min(init[j], d-sum[j]);
                if (init[j] < -INI)
                    fail();
            }
        }
    }

    for (int i = 0; i < n; i++)
        sum[i] = init[i];

    for (int i = 0; i < m; i++) {
        ty = op[i][0]; l = op[i][1]-1; r = op[i][2]; d = op[i][3];

        if (ty == 1) {
            for (int j = l; j < r; j++)
                sum[j] += d;
        } else {
            bool ok = 0;
            for (int j = l; j < r; j++) {
                ok |= (sum[j] == d);
            }

            if (!ok)
                fail();
        }
    }
    printf("YES\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", (int) init[i]);
    }
}
