#include <bits/stdc++.h>

using namespace std;

const int N = 100007;
const int MOD = 1000000009;

typedef unsigned long long int num;

#define ff first
#define ss second

set<int> down[N], up[N];
set<int>::iterator iter;
num pot[N];
int dep[N];
int n;
int x, y;
num res;

map<pair<int, int>, int> mp;
map<pair<int, int>, int>::iterator it;
pair<int, int> key;
set<int> pq;

int main () {
    scanf("%d", &n);

    pot[0] = 1ull;
    for (int i = 0; i < n; i++) {
        if (i)
            pot[i] = (pot[i-1]*(num)n)%MOD;
        scanf("%d %d", &key.ff, &key.ss);
        mp.insert(make_pair(key, i));
        
        key.ff--;
        key.ss--;
        for (int k = 0; k < 3; k++) {
            it = mp.find(key);
            if (it != mp.end()) {
                down[i].insert(it->ss);
                up[it->ss].insert(i);
            }
            key.ff++;
        }

        key.ff -= 3;
        key.ss += 2;
        for (int k = 0; k < 3; k++) {
            it = mp.find(key);
            if (it != mp.end()) {
                up[i].insert(it->ss);
                down[it->ss].insert(i);
            }
            key.ff++;
        }
    }


    for (int i = 0; i < n; i++) {
        if (down[i].size() == 1)
            dep[*(down[i].begin())]++;
    }

    for (int i = 0; i < n; i++)
        if (dep[i] == 0)
            pq.insert(i);

    bool pl = 1;
    int u;
    int left = n;
    while (!pq.empty()) {
        if (pl) {
            u = *(pq.rend());
            pq.erase(u);
        } else {
            u = *(pq.begin());
            pq.erase(pq.begin());
        }

        res += (pot[--left]*(num)u)%MOD;
        res %= MOD;

        if (down[u].size() == 1) {
            dep[*down[u].begin()]--;
            if (dep[*down[u].begin()] == 0)
                pq.insert(*down[u].begin());
        }
        for (iter = down[u].begin(); iter != down[u].end(); iter++) {
            up[*iter].erase(u);
        }
        
        for (iter = up[u].begin(); iter != up[u].end(); iter++) {
            down[*iter].erase(u);
            if (down[*iter].size() == 1) {
                if (dep[*(down[*iter].begin())] == 1)
                    pq.erase(*(down[*iter].begin()));
                dep[*(down[*iter].begin())]++;
            }
        }

        pl = !pl;
    }

    printf("%d\n", (int)res);
}
