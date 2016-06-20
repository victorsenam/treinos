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
int seq[2][N], ss[2], tt[2]; 

void join () {
    if (ss[!q] == 0) return;
    if (tt[!q] < tt[q]) q = !q;

    for (int i = 0; i < ss[q]; i++)
        seq[q][i] += ss[!q];
    for (int i = 0; i < tt[!q]-tt[q]; i++)
        seq[q][ss[q]++] = ss[q]-1+ss[!q];
    for (int i = 0; i < ss[!q]; i++)
        seq[q][ss[q]++] = seq[!q][i];

    tt[q] = max(tt[q], tt[!q]);
}

inline void justput (int x) {
    if (x == 1) return;
    for (int i = 0; i < x; i++)
        seq[q][ss[q]+i] = ss[q]+x-i-1;
    ss[q] += x;
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
            int bs = rand()%bc + 2;
            k = aux;
            //DEBUG("k_%d = %d", bs, 0);

            seq[0][0] = seq[1][0] = 0;
            ss[0] = tt[0] = 0;
            ss[1] = tt[1] = 0;
            q = 0;
            
            int i = 0;
            while (k) {
                if (k%bs != 0) {
                    ss[q] = 0;
                    tt[q] = 0;
                    
                    putnum(k%bs);
                    //DEBUG("+%d", k%bs);
                    for (int j = 0; j < i; j++) {
                        //DEBUG("*%d", bs);
                        putnum(bs);
                    }

                    join();
                    q = !q;

                    if (ss[!q] == 0)
                        ss[!q] = tt[!q] = 1;
                }
                k /= bs;
                i++;
            }
            //DEBUG("\n");

            if (ss[!q] <100)
                ok = 1;
        }

        if (!ok) return 1;

        printf("%d\n", ss[!q]);
        for (int i = 0; i < ss[!q]; i++)
            printf("%d ", seq[!q][i]+1);
        printf("\n");
    }
}
