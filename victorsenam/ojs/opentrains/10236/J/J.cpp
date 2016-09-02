#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e6+7;

struct node {
    ll x;
    ll i;
    ll k;

    bool operator < (const node & ot) const {
        return x < ot.x;
    }
};

ll n, t, opt;
priority_queue<node> pq;
node res[N], rs;
int p[N];
ll ls[N];

bool cmp_t (int a, int b) {
    return res[a].i < res[b].i;
}

ll brute (int n, ll x, ll k) {
    if (n == 0) return 0;
    return min(brute(n-1, 1+k+1, k+1) + 1 + t, brute(n-1, x+k, k) + x);
}

ll go (ll qt) {
    while (!pq.empty()) pq.pop();

    ll cost = 0;
    ll mini = (n*n);
    for (ll k = 1, st = 0; st < qt && (pq.size() < n || pq.top().x != 1); k++, st++) {
        for (ll x = 1; x <= t+1 && st < qt; x += k, st++) {
            if (pq.size() == n) {
                node rm = pq.top();
                pq.pop();

                cost -= rm.x;
            }
            
            node aux;
            aux.x = x;
            aux.i = st;
            aux.k = k;
            pq.push(aux);

            cost += aux.x;
            if (pq.size() == n && cost < mini) {
                opt = st;
                mini = cost;
            }
        }
        cost += t;
    }
    return mini;
}

int main () {
    while (scanf("%lld %lld", &n, &t) != EOF) {
        ll sol = go(n*n);
        go(opt+1);

        printf("%lld\n", sol);

        for (int i = 0; i < n; i++)
            ls[i] = 0;

        ll cnt = 0;
        while (!pq.empty()) {
            ll kk = pq.top().k;
            ls[kk]++;
            cnt = max(cnt, kk);
            pq.pop();
        }

        printf("%lld\n", cnt-1);
        ll acc = 0;
        for (int i = 1; i < cnt; i++) {
            acc += ls[i];
            printf("%lld ", acc);
        }
        printf("\n");
    }
}
