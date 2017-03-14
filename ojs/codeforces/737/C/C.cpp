#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5+7;

int n, s;
int a[N];

int get (int crr, int i, int need, int zer) {
    int curr = 0;

    curr += zer;
    need -= min(zer, need);

    int rg = n-i;
    curr += rg;
    need -= min(rg, need);

    curr += need;
    return curr;
}

int main () {
    scanf("%d %d", &n, &s);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    bool ok = (a[s-1] == 0);
    a[s-1] = 0;

    sort(a, a+n);

    int i = 0;
    int ls = 0;

    int need = 0;
    int zer = 0;

    int best = n;
    int crr;

    for (crr = 0; i < n; crr++) {
        while (i < n && a[i] == crr) i++;

        int cnt = i - ls;
        ls = i;

        if (crr == 0) {
            zer = cnt - 1;
        } else {
            if (cnt == 0) {
                need++;
            }
            
            best = min(best, get(crr, i, need, zer));
        }
    }
    best = min(best, get(crr, n, need, zer));

    printf("%d\n", best + !ok);
}
