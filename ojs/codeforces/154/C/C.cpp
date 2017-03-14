#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef vector<int> vi;
typedef long long int num;

const int N = 1000007;

vi adj[2][N];
int n, m;
int a, b;
num res;

bool cmpv (const vi & a, const vi & b) {
    if (a.size() == b.size())
        return a < b;
    return a.size() < b.size();
}

int main () {
    scanf("%d %d", &n, &m);

    res = 0;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj[0][a].push_back(b);
        adj[0][b].push_back(a);
        adj[1][a].push_back(b);
        adj[1][b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        adj[1][i].push_back(i);
        sort(adj[0][i].begin(), adj[0][i].end());
        sort(adj[1][i].begin(), adj[1][i].end());
    }
    
    sort(adj[0], adj[0]+n, cmpv);
    sort(adj[1], adj[1]+n, cmpv);

    num hi, i;

    num ans = 1ll;
    for (int i = 1; i < n; i++) {
        if (adj[0][i].size() == adj[0][i-1].size() && adj[0][i] == adj[0][i-1])
            ans++;
        else {
            res += ans*(ans-1ll)/2ll;
            ans = 1ll;
        }
    }
    res += ans*(ans-1ll)/2ll;

    ans = 1ll;
    for (int i = 1; i < n; i++) {
        if (adj[1][i].size() == adj[1][i-1].size() && adj[1][i] == adj[1][i-1])
            ans++;
        else {
            res += ans*(ans-1ll)/2ll;
            ans = 1ll;
        }
    }
    res += ans*(ans-1ll)/2ll;

    printf("%lld\n", res);
}
