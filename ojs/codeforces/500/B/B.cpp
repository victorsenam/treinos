#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

int uf[N], wf[N];
deque<int> v[N];
int n;
int p[N];

int find (int i) {
    if (i == uf[i]) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ((i = find(i)) == (j = find(j))) return;
    if (wf[i] < wf[j]) swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d ", p+i);
        p[i]--;
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            char a;
            scanf(" %c", &a);
            if (a == '1')
                join(p[i], p[j]);
        }

    for (int i = 0; i < n; i++)
        v[find(i)].push_back(i);

    for (int _i = 0; _i < n; _i++) {
        int i = p[_i];
        printf("%d ", v[find(i)].front()+1);
        v[find(i)].pop_front();
    }
    printf("\n");
}
