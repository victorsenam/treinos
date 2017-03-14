#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int p[N], x[N], y[N];
int n, k;
multiset<int> s;
multiset<int>::iterator it;

bool cmp_t (int i, int j) {
    if (y[i] == y[j])
        return x[i] < x[j];
    return y[i] < y[j];
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", x+i, y+i);
        p[i] = i;
    }

    int res = 0;
    sort(p, p+n, cmp_t);
    for (int i = 0; i < k; i++)
        s.insert(0);

    for (int i = 0; i < n; i++) {
        it = s.upper_bound(x[p[i]]);
        if (it == s.begin())
            continue;

        --it;
        res++;

        s.erase(it);

        s.insert(y[p[i]]);
    }

    printf("%d\n", res);
    
}
