#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 24;
const int K = 50007;

map<string, pair<num, string> > bil;
map<string, num> cit_mon;
map<string, int> cit_res;
set<pair<num, string> > s;
vector<pair<string, string> > evt[K];
int n, k, m;
char ta[N], tb[N];
num a;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %s %s %llu", ta, tb, &a);
        bil[ta] = make_pair(a, (string) tb);
        cit_mon[tb] += a;
    }

    for (auto it = cit_mon.begin(); it != cit_mon.end(); it++)
        s.insert(make_pair(it->second, it->first));
    
    scanf("%d %d", &m, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d %s %s", &n, ta, tb);
        evt[n].push_back(make_pair((string) ta, (string) tb));
    }

    n = 0;
    for (int i = 1; i <= m; i++) {
        auto it = s.rbegin();
        auto jt = it;
        jt++;

        if (s.rend() == jt || it->first != jt->first)
            cit_res[it->second]++;

        for (int j = 0; j < evt[i].size(); j++) {
            string sa = evt[i][j].first;
            string sb = evt[i][j].second;
            pair<num, string> & aux = bil[sa];
            s.erase(make_pair(cit_mon[aux.second], aux.second));
            s.erase(make_pair(cit_mon[sb], sb));

            cit_mon[aux.second] -= aux.first;
            cit_mon[sb] += aux.first;

            s.insert(make_pair(cit_mon[aux.second], aux.second));
            s.insert(make_pair(cit_mon[sb], sb));

            aux.second = sb;
        }
    }

    for (auto it = cit_res.begin(); it != cit_res.end(); it++)
        printf("%s %d\n", it->first.c_str(), it->second);
}
