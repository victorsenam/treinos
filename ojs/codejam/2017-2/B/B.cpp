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

const int N = 1e3+7;

int ts, tt, n, m, p[N], b[N], c;
vector<int> cm[2];
pii ord[N];

int main () {
    scanf("%d", &ts);
    
    for (tt = 1; tt <= ts; tt++) {
        printf("Case #%d: ", tt);
        scanf("%d %d %d", &n, &c, &m);

        cm[0].clear();
        cm[1].clear();

        int k = 0;
        int ones = 0;
        for (int i = 0; i < m; i++) {
            scanf("%lld %lld", &ord[i].first, &ord[i].second);
            ord[i].second--;
            if (ord[i].first == 1)
                ones++;

            cm[ord[i].second].push_back(ord[i].first);
        }

        k = max(cm[0].size(), cm[1].size());

        if (ones <= k) {
            if (cm[0].size() < cm[1].size())
                swap(cm[0], cm[1]);
            // 0 é maior

            sort(cm[0].begin(), cm[0].end());
            sort(cm[1].begin(), cm[1].end(), [] (int i, int j) {return i > j;});

            int conf = 0;
            int q[2] = {0,0};
            int quem = -1;
            for (int i = 0; i < cm[1].size(); i++) {
                if (cm[0][i] == cm[1][i]) {
                    conf++;
                    assert(quem == -1 || quem == cm[0][i]);
                    quem = cm[0][i];
                }
            }

            for (int i = 0; i < cm[0].size(); i++)
                if (cm[0][i] != quem)
                    q[0]++;

            for (int i = 0; i < cm[1].size(); i++)
                if (cm[1][i] != quem)
                    q[1]++;

            conf = max(0, conf - min(q[0], q[1]));

            printf("%d %d\n", k, conf);
        } else {
            printf("%d 0\n", ones);
        }
    }
}
