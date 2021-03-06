#include <bits/stdc++.h>

using namespace std;

const int N = 51;
const int M = 501;

int m, n;
int uf[N*M], wf[N*M];
int a;

int find (int i) {
    if (uf[i] == i)
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
    uf[j] = uf[i];
}

int main () {
    scanf("%d %d", &m, &n);

    int res = 0;

    for (int i = 0; i < m; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &a);
            a--;
            if (i == a)
                continue;
            join(a, i);
            res++;
        }
    }

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (find(i) == i && wf[i] != 1)
            cnt++;
    }
    if (cnt > 0)
        cnt--;
    res += cnt;
    printf("%d\n", res);
}
