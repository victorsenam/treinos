#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 200007;

int uf[N], wf[N];
int pr[N];
int frs;
int n;

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ((i = find(i)) == (j = find(j))) return;
    if (wf[i] > wf[j]) swap(i, j);
    wf[j] += wf[i];
    uf[i] = j;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }


    frs = -1;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", pr+i);
        pr[i]--;
        if (pr[i] == i)
            frs = i;
    }

    for (int i = 0; i < n; i++) {
        if (find(pr[i]) == find(i) || pr[i] < 0 || pr[i] >= n) {
            if (frs == -1) {
                frs = i;
                pr[i] = i;
            } else {
                if (i == frs) cnt--;
                pr[i] = frs;
            }
            cnt++;
        }
        join(pr[i], i);
    }

    printf("%d\n", cnt);
    for (int i = 0; i < n; i++)
        printf("%d ", pr[i]+1);

}
