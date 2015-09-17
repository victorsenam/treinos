#include <bits/stdc++.h>

using namespace std;

const int N = 3007;
const int S = 23;

map<string, int> mp;
int ps[N];
deque<pair<int, int> > q;
pair<int, int> aux, att;
int n, m;
int a;
char temp[S];

int main () {
    scanf("%d", &n);

    mp.clear();
    for (int i = 0; i < n; i++) {
        scanf("%d of %s", &a, temp);

        if (mp.find(temp) == mp.end())
            mp[temp] = mp.size()-1;

        ps[mp[temp]] = a;
    }

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d of %s", &a, temp);

        if (mp.find(temp) == mp.end()) {
            mp[temp] = mp.size()-1;
            ps[mp.size()-1] = 0;
        }

        aux.first = mp[temp];
        aux.second = a;
        q.push_back(aux);
    }

    int res = 0;
    while (!q.empty()) {
        aux = q.front();
        q.pop_front();

        res++;
        if (ps[aux.first] >= aux.second)
            ps[aux.first] -= aux.second;
        else if (ps[aux.first] > 0) {
            if (q.empty())
                break;

            att = q.front();
            q.pop_front();
            q.push_front(make_pair(aux.first, ps[aux.first]));
            q.push_front(att);
        }
    }

    printf("%d\n", res);
}
