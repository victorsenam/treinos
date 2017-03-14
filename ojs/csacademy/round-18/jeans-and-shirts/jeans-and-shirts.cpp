#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+8;

int n, m, k;
int v[N], c[N];

int main () {
    scanf("%d %d %d", &n, &m, &k);

    int a;
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }

    int res = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &a);

        for (int j = 0; j < n; j++)
            if (abs(a-c[i]) >= k)
                res++;
    }

    printf("%d\n", res);

}
