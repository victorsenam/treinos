#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 300007;
const int M = 1000007;

int nxt[M], len[M];
int qr[N][3], p[N];
int qu[M], qi, qf;
int n, qs;
int v[N];

int val (int i) {
    if (len[i] == 0) {
        nxt[i] = i;
        return 0;
    }
    len[i] += val(nxt[i]);
    nxt[i] = nxt[nxt[i]];
    return len[i];
}

bool cmp_t (int i, int j) {
    if (qr[i][1] != qr[j][1])
        return qr[i][1] < qr[j][1];
    if (qr[i][2] != qr[j][2])
        return qr[i][2] < qr[j][2];
    return qr[i][0] < qr[j][0];
}

int main () {
    scanf("%d %d", &n, &qs);
    n += qs;

    for (int i = 0; i < n; i++) {
        qr[i][2] = (i >= n-qs);
        scanf("%d %d", &qr[i][0], &qr[i][1]);
        p[i] = i;
        v[i] = -1;
    }

    sort(p, p+n, cmp_t);


    int cm = 0;
    for (int ii = 0; ii < n; ii++) {
        int i = p[ii];
        //printf("%d %d %d\n", qr[i][0], qr[i][1], qr[i][2]);

        if (qr[i][2] == 0) {
            while (cm <= qr[i][0]) {
                nxt[cm] = qr[i][1]+1;
                len[cm] = 1;
                cm++;
            }
        } else {
            v[i] = val(qr[i][0]);
        }
    }
    for (int i = 0; i < n; i++)
        if (v[i] >= 0)
            printf("%d\n", v[i]);
}
