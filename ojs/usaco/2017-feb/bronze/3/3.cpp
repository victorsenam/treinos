#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1000007;
int res;
int n;
int a[N],b[N],p[N];

int main () {
    freopen("cowqueue.in", "r", stdin);
    freopen("cowqueue.out", "w", stdout);
    
    res = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i], &b[i]);
        p[i] = i;
    }

    sort(p, p+n, [] (int i, int j) {
        return a[i] < a[j];
    });

    for (int i = 0; i < n; i++) {

        res = max(res, a[p[i]]);
        res += b[p[i]];
    }
    printf("%d\n", res);
}
