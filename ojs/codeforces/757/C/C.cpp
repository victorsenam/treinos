#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

const int N = 1e6+7;
const ll MOD = 1e9+7;

vector<int> pkmn[N];
vector<pii> gyms[N];
int p[N];
ll fat[N];
int n, m;
ll rr[N], rs;

bool cmp_t (int i, int j) {
    if (gyms[i].size() != gyms[j].size())
        return gyms[i].size() < gyms[j].size();
    for (int k = 0; k < gyms[i].size(); k++)
        if (gyms[i][k] != gyms[j][k])
            return gyms[i][k] < gyms[j][k];
    return 0;
}

int main () {
    fat[0] = 1;
    for (ll i = 1; i < N; i++)
        fat[i] = (fat[i-1]*i)%MOD;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        int q;
        scanf("%d", &q);

        for (int j = 0; j < q; j++) {
            int a;
            scanf("%d", &a);
            a--;
            pkmn[i].push_back(a);
        }

        sort(pkmn[i].begin(), pkmn[i].end());
        for (int j = 0; j < q;) {
            int sz = 0;
            while (j+sz < q && pkmn[i][j] == pkmn[i][j+sz]) sz++;
            gyms[pkmn[i][j]].push_back(pii(i, sz));
            j += sz;
        }
    }

    for (int i = 0; i < m; i++) {
        sort(gyms[i].begin(), gyms[i].end());

        //printf("%d :", i);
        //for (int j = 0; j < gyms[i].size(); j++)
            //printf(" (%d,%d)", gyms[i][j].first, gyms[i][j].second);
        //printf("\n");
        p[i] = i;
    }

    sort(p, p+m, cmp_t);
    for (int i = 0; i < m; i++) {
        if (!i || cmp_t(p[i-1], p[i])) {
            rr[rs] = 1;
            rs++;
        } else {
            //printf("(%d,%d)\n", p[i-1], p[i]);
            rr[rs-1]++;
        }
    }

    ll res = 1;
    for (int i = 0; i < rs; i++)
        res = (res*fat[rr[i]])%MOD;
    printf("%lld\n", res);
}
