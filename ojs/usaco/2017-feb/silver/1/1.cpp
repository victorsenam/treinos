#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e4+7;

struct node {
    int a,b;

    bool operator < (const node & ot) const {
        return b > ot.b;
    }
};

priority_queue<node> pq;
int n, m;

int v[N];
node x[N];

int main () {
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);
    
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    for (int i = 0; i < m; i++)
        scanf("%d %d", &x[i].a, &x[i].b);

    sort(v, v+n);
    sort(x, x+m, [] (node x, node y) {
        return x.a < y.a;
    });

    int l = 0;
    int res = 0;
    for (int i = 0; i < n; i++) {
        while (l < m && x[l].a <= v[i]) {
            pq.push(x[l]);
            l++;
        }

        while (!pq.empty() && pq.top().b < v[i])
            pq.pop();

        if (!pq.empty()) {
            res++;
            pq.pop();
        }
    }
    printf("%d\n", res);
}
