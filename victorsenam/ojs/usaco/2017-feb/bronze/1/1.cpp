#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 13;

int v[N];
int n;

int main () {
    freopen("crossroad.in", "r", stdin);
    freopen("crossroad.out", "w", stdout);
    scanf("%d", &n);

    for (int i = 0; i < N; i++)
        v[i] = -1;

    int res = 0;

    for (int i = 0; i < n; i++) {
        int id, a;
        scanf("%d %d", &id, &a);

        if (v[id] == a)
            res++;
        v[id] = !a;
    }

    printf("%d\n", res);
}
