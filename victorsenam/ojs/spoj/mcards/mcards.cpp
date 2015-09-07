#include <bits/stdc++.h>

using namespace std;

const int N = 103;
const int K = 4;

int c, n, a, b;
pair<int, int> v[K*N];
int perm[K];
int lis[N];
int rs, ps, maxi;

int main () { 
    scanf("%d %d", &c, &n);

    maxi = 0;
    for (int i = 0; i < c*n; i++) {
        scanf("%d %d", &v[i].first, &v[i].second);
        v[i].first--; v[i].second--;
    }

    for (int i = 0; i < c; i++)
        perm[i] = i;

    do {
        rs = 0;

        for (int i = 0; i < c*n; i++) {
            a = perm[v[i].first]*n + v[i].second;
            ps = lower_bound(lis, lis+rs, a) - lis;
            lis[ps] = a;
            if (ps == rs)
                rs++;
        }

        maxi = max(maxi, rs);
    } while (next_permutation(perm, perm+c));

    printf("%d\n", n*c - maxi);
}
