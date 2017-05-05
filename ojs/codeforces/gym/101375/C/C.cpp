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

const int N = 5e3+7;

int q;
ll v[N][4];

ll sq (ll x) {
    return x*x;
}

ll dist (int i, int j) {
    return sq(v[i][0] - v[j][0]) + sq(v[i][1] - v[j][1]);
}

int main () {
    scanf("%d", &q);

    int t = 0;
    for (int i = 0; i < q; i++) {
        char c;
        scanf(" %c", &c);
        for (int j = 0; j < 3; j++)
            scanf("%lld", &v[t][j]);

        if (c == 'A') {
            v[t][3] = 1;
            for (int j = 0; j < t; j++)
                if (v[j][3] && dist(t,j) < sq(v[j][2] + v[t][2])) {
                    v[t][3] = 0;
                }

            if (v[t][3])
                printf("Ok\n");
            else
                printf("No\n");
        } else {
            v[t][3] = 1;
            for (int j = 0; j < t; j++)
                if (v[j][3] && v[j][0] == v[t][0] && v[j][1] == v[t][1] && v[j][2] == v[t][2]) {
                    v[t][3] = 0;
                    v[j][3] = 0;
                }

            if (v[t][3])
                printf("No\n");
            else
                printf("Ok\n");
            v[t][3] = 0;
        }
        t++;
    }
}
