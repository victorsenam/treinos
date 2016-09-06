#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

struct node {
    int k;
    int i;
    ll x;

    bool operator < (const node & ot) const {
        if (x != ot.x)
            return x < ot.x;
        if (i != ot.i)
            return i < ot.i;
        return k < ot.k;
    }
};

int n, t;
ll cost, res;
int rs, rind, cnt;
int qs;
priority_queue<node> pq;
node aux, att;
vector<node> r;
vector<int> v;

ll brute (int i, int k, int n) {
    if (n == 0) return 0;
    return min(brute(i+k+1, k, n-1) + i, brute(1+k+2, k+1, n-1) + 1 + t);
}

int main () {
    while(true) {
        scanf("%d %d", &n, &t);
        //n = rand() % 20 + 1, t = rand() % (n + 10);
        r.clear();
        v.clear();
        while (pq.size()) pq.pop();
        qs = rs = rind = cnt = cost = res = 0;

        rind = cost = res = 0;
        bool ok  =1;
        for (int k = 1; ok && (k <= t || qs < n); k++) {
            cnt = 1;
            for (int i = 1; i <= t+1; i += k) {
                cost += i;
                aux.k = k;
                aux.i = cnt++;
                aux.x = i;
                pq.push(aux);

                if (qs < n) {
                    qs++;
                    if (qs == n) {
                        res = cost;
                        rind = r.size();
                    }
                } else {
                    att = pq.top();
                    pq.pop();
                    r.push_back(att);
                    cost -= att.x;
                    if (cost < res) {
                        res = cost;
                        rind = r.size();
                    }
                }
            }
            cost += t;
            aux.i = cnt-1;
            r.push_back(aux);
        }

        ll acc = 0;
        int maxi = 0;

        for (int i = 0; i < rind; i++) {
            if (r[i].k - 1 >= v.size())
                v.push_back(r[i].i);
            else
                v[r[i].k-1] = r[i].i;
        }

        
        //printf("%lld\n", brute(1, 0, n));
        printf("%lld\n%d\n", res, int(v.size()));
        vector<int> p;
        for (int i = 0; i < v.size(); i++) {
            acc += v[i];
            p.push_back(acc);
            printf("%lld ", acc);
        }
        printf("\n");

        int k = 0;
        int vl = 1;
        ll ans = 0;
        int l = 0;
        for (int i = 0; i < n; i++) {
            ans += vl;
            if (l < p.size() && i + 1 == p[l]) {
                ans += t;
                k++;
                vl = 1;
                l++;
            } else {
                vl += k+1;
            }
        }

        if (res != ans) {
            printf("FODEU %d %d %lld\n", n, t, ans);
        }
        assert(res == ans);
    }
        

}
