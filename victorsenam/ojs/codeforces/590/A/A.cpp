#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

const int N = 5e5 + 7;

int n;
int v[N];
int r[2][N];
deque<pair<int, int> > q;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    int res = 0;
    int curr = 0;

    r[0][0] = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] == v[i-1])
            r[0][i] = 0;
        else
            r[0][i] = r[0][i-1] + 1;
    }

    r[1][n-1] = 0;
    for (int i = n-2; i >= 0; i--) {
        if (v[i] == v[i+1])
            r[1][i] = 0;
        else
            r[1][i] = r[1][i+1] + 1;
    }

    for (int i = 0; i < n; i++) {
        int loc = min(r[0][i], r[1][i]);
        res = max(res, loc);
        if (loc&1)
            v[i] = !v[i];
    }

    printf("%d\n", res);
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}
