#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;

int ts, tt, n, m, p[N], b[N], c;
pii ord[N];
int curr[N], usd[N][N];

int solve (int k, int verb = 0) {
    int res = 0;

    for (int i = 0; i < k; i++)
        curr[i] = n + 1;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < c; j++)
            usd[i][j] = 0;
    }

    for (int i = 0; i < m; i++) {
        int bst = -1;
        // tenta sem promover
        for (int j = 0; j < k; j++) {
            if (usd[j][b[i]])
                continue;
            if (curr[j] <= p[i]) // precisa promover
                continue;
            if (bst == -1 || curr[bst] >= curr[j])
                bst = j;
        }
        if (bst != -1)  {
            curr[bst] = p[i];
            usd[bst][b[i]] = 1;

            if (verb)
                debug("ticket (%d,%d) no carrinho %d na posi %d\n", p[i], b[i], bst, p[i]);

            continue;
        }

        // tenta promovendo
        for (int j = 0; j < k; j++) {
            if (usd[j][b[i]])
                continue;
            if (curr[j] == 1) // nao da pra promover aqui
                continue;
            if (bst == -1 || curr[bst] >= curr[j])
                bst = j;
        }
        if (bst != -1) {
            res++;
            curr[bst]--;
            usd[bst][b[i]] = 1;

            if (verb)
                debug("ticket (%d,%d) no carrinho %d na posi %d [PROM]\n", b[i], p[i], bst, curr[bst]);
        } else {
            return -1; // faiô
        }
    }

    return res;
}

int main () {
    scanf("%d", &ts);
    
    for (tt = 1; tt <= ts; tt++) {
        scanf("%d %d %d", &n, &c, &m);

        for (int i = 0; i < m; i++) {
            scanf("%lld %lld", &ord[i].first, &ord[i].second);
            ord[i].second--;
        }
        sort(ord, ord+m, [] (pii a, pii b) {
            if (a.first != b.first)
                return a.first > b.first;
            return a.second < b.second;
        });
        for (int i = 0; i < m; i++) {
            p[i] = ord[i].first;
            b[i] = ord[i].second;
        }

        int lo = 1, hi = m;

        while (lo < hi) {
            int mid = (lo+hi)/2;

            if (solve(mid) != -1)
                hi = mid;
            else
                lo = mid + 1;
        }

        printf("Case #%d: %d %d\n", tt, lo, solve(lo, 1));
    }
}
