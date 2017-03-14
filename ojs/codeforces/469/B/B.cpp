#include <bits/stdc++.h>

using namespace std;

const int N = 57;

int ta[N][2];
int tb[N][2];
int p, q, l, r, res;

int main ( ) {
    scanf("%d %d %d %d", &p, &q, &l, &r);

    for (int i = 0; i < p; i++)
        scanf("%d %d", ta[i], ta[i]+1);
    
    for (int i = 0; i < q; i++)
        scanf("%d %d", tb[i], tb[i]+1);

    for (int t = l; t <= r; t++) {
        bool ok = 0;
        for (int i = 0; i < p && !ok; i++) {
            for (int j = 0; j < q && !ok; j++) {
                if (ta[i][0] > tb[j][1]+t) continue;
                if (ta[i][1] < tb[j][0]+t) break;
                ok = 1;
            }
        }
        res += ok;
    }

    printf("%d\n", res);
}


