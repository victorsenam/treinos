#include <bits/stdc++.h>

using namespace std;

const int nn = 64;
const int n = 8;
const int m[4] = {1, -1, -n, n};
const int p[4] = {0, 1, n, n+1};
const char name[4] = {'A', 'B', 'C', 'D'};

int mat[nn];
set<int> sts;
int inis[4];

void tryIt (int s) {
    int a[4] = {s%nn, (s/nn)%nn, (s/nn/nn)%nn, (s/nn/nn/nn)};
    int b[4], t;
    bool cha;
    for (int k = 0; k < 4; k++) {
        for (int car = 0; car < 4; car++)
            b[car] = a[car];

        cha = 1;
        while (cha) {
            cha = 0;
            for (int car = 0; car < 4; car++) {
                bool ok = 1;
                for (int posi = 0; posi < 4 && ok; posi++) {
                    if (m[k]/n == 0 && (b[car]+p[posi])/n != (b[car]+p[posi]+m[k])/n)
                        ok = 0;
                    else if (b[car]+p[posi]+m[k] >= nn || b[car]+p[posi]+m[k] < 0)
                        ok = 0;
                    else {
                        if (mat[b[car]+p[posi]+m[k]] == '#')
                            ok = 0;
                        for (int out = 0; out < 4 && ok; out++) {
                            if (out == car) continue;
                            for (int posj = 0; posj < 4 && ok; posj++) {
                                if (b[car]+p[posi]+m[k] == b[out]+p[posj])
                                    ok = 0;
                            }
                        }
                    }
                }
                if (ok) {
                    cha = 1;
                    b[car] += m[k];
                }
            }
        }

        
        t = (b[0]+nn*(b[1]+nn*(b[2]+nn*b[3])));
        if (sts.find(t) == sts.end()) {
            sts.insert(t);
            tryIt(t);
        }
    }
}

int main () {
    int t;
    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        for (int i = 0; i < 4; i++)
            inis[i] = -1;
        for (int i = 0; i < nn; i++) {
            scanf(" %c", mat+i);
            for (int j = 0; j < 4; j++)
                if (mat[i] == name[j] && inis[j] == -1)
                    inis[j] = i;
        }
        sts.clear();
        tryIt(inis[0]+nn*(inis[1]+nn*(inis[2]+nn*inis[3])));
        printf("Case %d: %d\n", c, sts.size());
    }
}
