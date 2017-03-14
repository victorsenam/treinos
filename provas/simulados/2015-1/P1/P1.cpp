#include <queue>
#include <climits>
#include <cmath>
#include <string>
#include <map>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define N 1001

map<string, int> m;
map<string, int>::iterator it;
char temp[21];
vector<pair<unsigned long long int, unsigned long long int> > pec[N];
priority_queue<unsigned long long int> pq;
unsigned long long int b;
int t;
int n;
int pcs;
int pos;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %llu", &n, &b);
        pcs = 0;

        while (!pq.empty()) pq.pop();

        for (int i = 0; i < n; i++) {
            scanf(" %s", temp);            
            it = m.find(temp);
            if (it == m.end()) {
                m.insert(make_pair(temp, pcs));
                pos = pcs;
                pec[pos].clear();
                pcs++;
            } else {
                pos = it->second;
            }

            scanf(" %s", temp);
            
            unsigned long long int pric, qual;
            scanf("%llu %llu", &pric, &qual);
            pec[pos].push_back(make_pair(pric, qual));
            pq.push(qual);
        }

        unsigned long long int q_min, p_min, cost;
        int i, j;
        while (!pq.empty()) {
            q_min = pq.top();
            cost = 0;
            for (i = 0; i < pcs; i++) {
                p_min = LLONG_MAX;
                for (j = 0; j < pec[i].size(); j++) {
                    if (pec[i][j].second < q_min) continue;
                    if (pec[i][j].first < p_min) p_min = pec[i][j].first;
                }
 //               printf("%llu + %llu = ", cost, p_min);
                cost += p_min;
   //             printf("%llu\n", cost);
                if (cost > b) break;
            }
     //       printf("\n");
            if (i == pcs) break;
            pq.pop();
        }

        if (pq.empty()) printf("0\n");
        else printf("%llu\n", pq.top());
    }
}
