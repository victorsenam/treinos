#include <bits/stdc++.h>
using namespace std;

const int N = 20007;
const int K = 5007;

int n, k;
int qr[K][2];
int rem[N];
int res[N];
int p[N];
int uf[N], wf[N];
int t;
int turn;

int find (int i) {
    if (i == uf[i])
        return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j)
        return;
    if (wf[i] < wf[j])
        swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int main ( ) {
    scanf("%d", &t);
    int ts = 0;
    while (t--) {
        printf("Case #%d:\n", ++ts);
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++) {
            uf[i] = i;
            wf[i] = 1;
        }
        
        for (int i = 0; i < n; i++) {
            scanf("%d", p+i);
            p[i]--;
            rem[i] = 0;
        }

        for (int i = 0; i < k; i++) {
            char c;
            scanf(" %c", &c);
            if (c == 'C') {
                qr[i][0] = -1;
                scanf("%d", &qr[i][1]);
                qr[i][1]--;
                if (qr[i][1] == -1)
                    continue;
                rem[qr[i][1]]++;
            } else {
                scanf("%d %d", &qr[i][0], &qr[i][1]);
                qr[i][0]--;
                qr[i][1]--;
            }
        }

        for (int i = 0; i < n; i++) {
            if (!rem[i] && p[i] >= 0)
                join(i, p[i]);
        }

        for (int i = k-1; i >= 0; i--) {
            if (qr[i][0] == -1) {
                res[i] = -1;
                if (p[qr[i][1]] == -1)
                    continue;
                rem[qr[i][1]]--;
                if (rem[qr[i][1]] == 0)
                    join(qr[i][1], p[qr[i][1]]);
            } else {
                if (find(qr[i][1]) == find(qr[i][0]))
                    res[i] = 1;
                else
                    res[i] = 0;
            }
        }

        for (int i =0 ; i < k; i++) {
            if (res[i] == 1)
                printf("YES\n");
            else if (res[i] == 0)
                printf("NO\n");
        }
    }
}
