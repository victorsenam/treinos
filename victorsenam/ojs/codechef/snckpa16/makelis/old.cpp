#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 10000;
const int bc = 26;
int ts;
ll k;
bool q;
int bs;
int tt[2]; 
deque<int> seq[2];

void join () {
    if (seq[!q].size() == 0) q = !q;
    if (seq[q].size() == 0) return;

    if (tt[!q] < tt[q] || (tt[q] == tt[!q] && seq[!q].size() < seq[q].size())) q = !q;

    int sa = seq[q].size();
    int sb = seq[!q].size();

    for (int i = 0; i < tt[!q]-tt[q]; i++)
        seq[!q].push_front(sa+i+sb);

    while (seq[q].size()) {
        seq[!q].push_front(seq[q].back()+sb);
        seq[q].pop_back();
    }

    tt[q] = tt[!q] = max(tt[q], tt[!q]);
}

inline void justput (int x) {
    if (x == 1) return;
    int s = seq[q].size();
    for (int i = 0; i < x; i++)
        seq[q].push_back(s+x-i-1);
    tt[q]++;
}

void putnum (ll x) {
    for (ll i = 2; i*i <= x; i++) {
        while (x%i == 0) {
            justput(i);
            x /= i;
        }
    }
    justput(x);
}

int main () {
    srand(time(NULL)); rand(); rand();
    scanf("%d", &ts);

    int mb = 2;
    while (ts--) {
        scanf("%lld", &k);

        if (k == 1) {
            printf("1\n1\n");
            continue;
        }

        int aux = k;
        bool ok = 0;
        while (!ok) {
            bs = rand()%bc + 2;
            k = aux;

            seq[0].clear();
            seq[1].clear();
            tt[0] = tt[1] = 0;

            if (k&1) {
                tt[1] = 1;
                seq[1].push_back(1);
                k ^= 1;
            }
            
            q = 0;
            
            int i = 0;
            while (k) {
                if (k%bs != 0) {
                    seq[q].clear();
                    tt[q] = 0;
                    
                    putnum(k%bs);
                    for (int j = 0; j < i; j++)
                        putnum(bs);

                    join();
                }
                k /= bs;
                i++;
            }

            if (seq[!q].size() < 100)
                ok = 1;
        }

        if (!ok) return 1;

        printf("%d\n", (int) seq[!q].size());
        while (seq[!q].size()) {
            printf("%d ", seq[!q].front()+1);
            seq[!q].pop_front();
        }
        printf("\n");
    }
}
