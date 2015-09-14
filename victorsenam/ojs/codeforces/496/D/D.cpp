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

#define N 100007

int n;
int a, m;
int scr[2][N];  // score at time
int ls;         // last to score
vector<pair<int, int> > res;

int main () {
    scanf("%d", &n);
    scr[0][0] = scr[0][1] = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        a--;
        ls = a;

        scr[a][i+1] = scr[a][i] + 1;
        scr[a^1][i+1] = scr[a^1][i];
    }

    for (int t = 1; t <= n; t++) {
        int last = 0;
        int nx[2];
        int ss[2] = {0,0};
        int ls = 0;

        while (last < n) {
            for (int i = 0; i < 2; i++)
                nx[i] = lower_bound(scr[i], scr[i]+n+1, scr[i][last]+t) - scr[i];

            if (nx[0] < nx[1]) {
                ss[0]++;
                last = nx[0];
                ls = 0;
            } else if (nx[0] > nx[1]) {
                ss[1]++;
                last = nx[1];
                ls = 1;
            } else
                break;
        }

        if (last < n || ss[ls] <= ss[ls^1])
            continue;
        else
            res.push_back(make_pair(ss[ls], t));
    }

    sort(res.begin(), res.end());

    printf("%d\n", res.size());
    for (int i = 0; i < res.size(); i++)
        printf("%d %d\n", res[i].first, res[i].second);
}
