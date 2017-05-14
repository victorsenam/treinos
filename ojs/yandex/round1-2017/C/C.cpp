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

const int M = 2e6;

int n, m;
pii ad[M];
int team[M];
vector<int> wr[M];

set<int> s;

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        if (u > v)
            swap(u, v);

        wr[v].push_back(u);
    }

    int cs = 0;
    for (int i = 0; i < n; i++) {
        for (int x : wr[i]) {
            if (s.find(team[x]) != s.end())
                s.erase(team[x]);
        }

        if (s.size() == 0)
            team[i] = ++cs;
        else
            team[i] = (*s.begin());
            
        s.insert(team[i]);
        for (int x : wr[i]) {
            s.insert(team[x]);
        }
    }

    printf("%d\n", cs);
    for (int i = 0; i < n; i++)
        printf("%d ", team[i]);
    printf("\n");
}
