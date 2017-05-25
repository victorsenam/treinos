#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

int ts;
ll n, k;

struct cut {
    int a, b, q;

    bool operator < (const cut & ot) const {
        if (a != ot.a)
            return a < ot.a;
        if (b != ot.b)
            return b < ot.b;
        return q < ot.q;
    }
};

int main () {
    scanf("%d", &ts);

    for (int tt = 1; tt <= ts; tt++) {
        printf("Case #%d: ", tt);
        scanf("%lld %lld", &n, &k);

        priority_queue<cut> pq;

        int c = 0;
        cut aux;
        aux.a = (n-1)/2;
        aux.b = n/2;
        aux.q = c++;
        pq.push(aux);

        while (!pq.empty()) {
            cut curr = pq.top();
            pq.pop();
            k--;

            if (!k) {
                printf("%lld %lld\n", curr.b, curr.a);
                break;
            }

            if (curr.a) {
                aux.a = (curr.a-1)/2;
                aux.b = (curr.a)/2;
                aux.q = c++;
                pq.push(aux);
            }

            if (curr.b) {
                aux.a = (curr.b-1)/2;
                aux.b = (curr.b)/2;
                aux.q = c++;
                pq.push(aux);
            }
        }
    }
}
