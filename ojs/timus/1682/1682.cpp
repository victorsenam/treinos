#include <bits/stdc++.h>

using namespace std;

const int K = 100007;

vector<int> nor[K], qua[K], sol;
int uf[3*K];
int we[3*K];
int k, a, b;

int find (int a) {
    if (uf[uf[a]] != uf[a])
        uf[a] = find(uf[a]);
    return uf[a];
}

int join(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) 
        return a;
    if (we[a] > we[b])
        swap(a, b);
    uf[a] = b;
    we[b] += we[a];
    return b;
}

int main () {
    scanf("%d", &k);

    for (int i = 0; i <= 3*k; i++) {
        uf[i] = i;
        we[i] = 1;
    }

    for (long long int i = 1; i <= 3*k; i++) {
        a = ((k-i)%k + k)%k;
        b = ((k-(i*i)%k)%k + k)%k;

        sol.clear();
        for (int j = 0; j < nor[b].size(); j++)
            sol.push_back(nor[b][j]);
        for (int j = 0; j < qua[a].size(); j++)
            sol.push_back(qua[a][j]);
        sort(sol.begin(), sol.end());
        int siz = unique(sol.begin(), sol.end()) - sol.begin();

        for (int j = 0; j < siz; j++) {
                if (find(i) == find(sol[j])) {
                printf("%d\n", (int) i);
                return 0;
            }
            join(i, sol[j]);
        }
        nor[i%k].push_back(i);
        qua[(i*i)%k].push_back(i);
    }
}
