#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 57;
const int K = 23;

int n, k;
vector<int> u[2];
vector<int> r;
int v[K];
set<vector<int> > s;

void solve (int i, int j) {
    r.push_back(j-i);
    if (i == j) 
        return;


    u[0].clear(); u[1].clear();
    for (int m = i+1; m < j; m++) {
        u[v[i] < v[m]].push_back(v[m]);
    }

    for (int m = 0; m < u[0].size(); m++)
        v[1+i+m] = u[0][m];
    for (int m = 0; m < u[1].size(); m++)
        v[1+i+m+u[0].size()] = u[1][m];

    solve(1+i, 1+i+u[0].size());
    solve(1+i+u[0].size(), j);
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++)
            scanf("%d", &v[j]);
        r.clear();

        solve(0, k);
        s.insert(r);
    }

    printf("%u\n", s.size());
}
