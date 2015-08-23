#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 500007

int n, m, a, h;
vector<int> hei[N];
vector<int> adj[N];
int lo, hi;
int ord;
bool acc[N][28];     // acumulada dos nos naquela altura ate tal posordem
int from[N];
int pos[N];
char str[N];

void dfs (int v, int h) {
    from[v] = ord;

    for (int i = 0; i < adj[v].size(); i++)
        dfs(adj[v][i], h+1);

    pos[v] = ord++;

    if (hei[h].size()) {
        for (int i = 0; i < 26; i++)
            acc[pos[v]][i] = acc[hei[h][hei[h].size()-1]][i];
        acc[pos[v]][str[v]-'a'] = !(acc[pos[v]][str[v]-'a']);
    } else {
        acc[pos[v]][str[v]-'a'] = 1;
    }

    hei[h].push_back(pos[v]);
}

int main () {
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; i++) {
        scanf("%d", &a);
        a--;
        adj[a].push_back(i);
    }

    scanf(" %s", str);

    ord = 1;
    dfs(0, 0);

    /*
    for (int i = 0; i < N; i++) {
        if (hei[i].size() == 0) break;
        for (int j = 0; j < hei[i].size(); j++)
            printf("%d ", hei[i][j]);
        printf("\n");
    }
    */

   // for (int i = 0; i < n; i++)
   //     printf("%d [%d,%d]\n", i, from[i], pos[i]);


    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &h);
        a--; h--;

        lo = lower_bound(hei[h].begin(), hei[h].end(), from[a]) - hei[h].begin() - 1;
        hi = upper_bound(hei[h].begin(), hei[h].end(), pos[a]) - hei[h].begin() - 1;
        if (lo == -1)
            lo = 0;
        else
            lo = hei[h][lo];

        if (hi == -1) {
            printf("Yes\n");
            continue;
        }
        hi = hei[h][hi];

        int cnt = 0;
        for (int j = 0; j < 26 && cnt < 2; j++)
            if (acc[lo][j] != acc[hi][j])
                cnt++;
        if (cnt < 2)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
