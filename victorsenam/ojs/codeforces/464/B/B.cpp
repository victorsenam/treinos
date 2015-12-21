#include <bits/stdc++.h>

using namespace std;

typedef int num;

num v[10][4];
int p[10];
num a[4][4];

void fail() {
    printf("NO\n");
    exit(0);
}

bool cmp_v (int i, int j) {
    for (int k = 0; k < 3; k++)
        if (v[i][k] != v[j][k])
            return v[i][k] < v[j][k];
    return i < j;
}

void bt (int k) {
    if (k == 8) {
        sort(p, p+8, cmp_v);

        num d = v[p[7]][0] - v[p[0]][0];
        if (d == 0)
            return;

        for (unsigned int i = 0; i < 8; i++)
            for (int j = 0; j < 3; j++)
                if (v[p[i]][j] != v[p[0]][j] + ((i&(1<<(2-j)))?d:0))
                    return;

        printf("YES\n");
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++)
                printf("%d ", v[i][j]);
            printf("\n");
        }
        exit(0);
    }

    do {
        bt(k+1);
    } while (next_permutation(v[k], v[k]+3));
}

int main () {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &v[i][j]);

    for (int i = 0; i < 8; i++) {
        sort(v[i], v[i]+3);
        p[i] = i;
    }

    bt(0);
    fail();
}
