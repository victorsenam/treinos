#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 40007;
const int M = 4000007;
const int A = 27;

struct trie {
    int n;
    int nx[M][A], es;
    int id[M], p[M], c[M];
    int qu[M], qi, qf;
    int f[M], g[M], p[M];

    void init () {
        es = 2;
    }

    void insert (int r, int i, char * s, int idx) {
        if (!s[i]) {
            id[r] = idx;
            return 0;
        }

        if (!nx[r][s[i]]) {
            p[es] = r;
            c[es] = s[i];
            nx[r][s[i]] = es++;
        }
        insert(nx[r][s[i]], i+1, s, idx);            
    }

    void build () {
        qi = qf = 0;

        for (int i = 0; i < A; i++) {
            if (!nx[1][i]) continue;
            q[qf] = nx[1][i];
            f[q[qf]] = 1;
            g[q[qf]] = 0;
            qf++;
        }

        while (qi < qf) {
            int u = qu[qi++];
            for (int i = 0; i < A; i++) {
            }
        }
    }
};

int main () {
       
}
