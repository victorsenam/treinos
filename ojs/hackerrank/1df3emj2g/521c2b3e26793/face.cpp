#include <bits/stdc++.h>

using namespace std;

int main () {
    int n, v, mtot, mat, a, ini;

    mtot = mat = ini = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        ini += a;
        if (a == 0) a = 1;
        else a = -1;

        mat = max(0, mat + a);
        mtot = max(mtot, mat);
    }

    printf("%d\n", ini+mtot);
}
