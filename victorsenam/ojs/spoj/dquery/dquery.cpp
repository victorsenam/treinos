#include <bits/stdc++.h>

using namespace std;

const int N = 30007;
const int M = 200007;

int n, m;
int bit[N];
int a[N];
int p[M];
int q[M][2];
int r[M];
set<pair<int, int> > s;
set<pair<int, int> >::iterator it;

int bitGet (int i) {
    int res = 0;
    for (i+=2; i > 0; i -= (i&-i))
        res += bit[i];
    return res;
}

void bitAdd (int i, int x) {
    for (i+=2; i <= n+7; i += (i&-i))
        bit[i] += x;
}

bool cmp_ord (int i, int j) {
    if (q[i][0] == q[j][0])
        return q[i][1] < q[j][1];
    return q[i][0] < q[j][0];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", a+i);
        it = s.lower_bound(make_pair(a[i], 0));
        if (it == s.end() || it->first != a[i])
            bitAdd(i, 1);
        s.insert(make_pair(a[i], i));
    }

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &q[i][0], &q[i][1]);
        q[i][0]--;
        q[i][1]--;
        p[i] = i;
    }
    sort(p, p+m, cmp_ord);

    int ls = 0;
    for (int i = 0; i < m; i++) {
        int j = p[i];
        for (ls = ls; ls < q[j][0]; ls++) {
            bitAdd(ls, -1);
            it = s.lower_bound(make_pair(a[ls], ls+1));
            if (it != s.end() && it->first == a[ls])
                bitAdd(it->second, 1);
        }
        r[j] = bitGet(q[j][1]);
    }

    for (int i = 0; i < m; i++)
        printf("%d\n", r[i]);
}
