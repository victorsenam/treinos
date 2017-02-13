#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5+7;

int bit[2][N];
int n;
int ps[N][2], v[N];

void add (int k, int i, int x) {
    for (i += 2; i < N; i+=(i&-i))
        bit[k][i] += x;
}

int get (int k, int i) {
    int x = 0;
    for (i += 2; i > 0; i-=(i&-i))
        x += bit[k][i];
    return x;
}

int main () {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    scanf("%d", &n);

    for (int i = 0; i < n+n; i++) {
        int a;
        scanf("%d", &a);
        a--;
        v[i] = a;
        swap(ps[a][0],ps[a][1]);
        ps[a][1] = i;
    }

    for (int i = 0; i < n; i++) {
        add(1, ps[i][0], 1);
        add(1, ps[i][1], -1);
    }

    int res = 0;
    
    for (int i = 0; i < 2*n; i++) {
        int a = v[i];
        if (ps[a][0] == i) {
            add(1, ps[a][0], -1);
            add(1, ps[a][1], 1);

            res += get(1, ps[a][1]);
        }
    }

    printf("%d\n", res);
}
