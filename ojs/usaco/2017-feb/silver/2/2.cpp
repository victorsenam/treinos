#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

bool v[N];
int n, k, b;
int cnt, res;

int main () {
    freopen("maxcross.in", "r", stdin);
    freopen("maxcross.out", "w", stdout);
    scanf("%d %d %d", &n, &k, &b);

    for (int i = 0; i < b; i++) {
        int a;
        scanf("%d", &a);
        v[a] = 1;
    }

    res = 0;
    for (int i = 1; i <= k; i++)
        cnt += !v[i];

    res = max(res, cnt);
    for (int i = 1; i + k <= n; i++) {
        cnt -= !v[i];
        cnt += !v[i+k];
        res = max(res, cnt);
    }

    printf("%d\n", max(0, k-res));
}
