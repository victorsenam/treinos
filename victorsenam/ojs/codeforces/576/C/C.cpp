#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 1000007;
const num MAXI = 2500000000ll;

int n;
int x[N], y[N], p[N];

bool cmp_x (int a, int b) {
    return x[a] < x[b];
}

bool cmp_y (int a, int b) {
    return y[a] < y[b];
}

num calculate() {
    num res = 0;
    for (int i = 1; i < n; i++) {
        res += abs(y[p[i]] - y[p[i-1]]) + abs(x[p[i]] - x[p[i-1]]);
        if (res > MAXI)
            return res;
    }
    return res;
}

void tenta (int l, int r, bool ty) {
    if (l + 1 >= r)
        return;

    if (ty) sort(p+l, p+r, cmp_x);
    else sort(p+l, p+r, cmp_y);

    int mid = rand()%(r-1) + l + 1;
    if (mid == r)
        mid--;
    tenta(l, mid, !ty);
    tenta(mid, r, !ty);
}

int main () {
    scanf("%d", &n);
    srand(time(NULL));
    rand(); rand();

    for (int i = 0; i < n; i++) {
        scanf("%d %d", x+i, y+i);
        p[i] = i;
    }

    bool ty = 0;
    while (calculate() > MAXI) tenta(0, n, (ty = !ty));

    for (int i = 0; i < n; i++)
        printf("%d ", p[i]+1);
    printf("\n");
}
