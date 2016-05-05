#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 500007;

int uf[N], wf[N];
int n, m, p;
char str[N];
char c;
int st[N], ss;
int l[N];
int fs[N], ls[N];

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ( (i = find(i)) == (j = find(j)) ) return;
    if (wf[i] < wf[j]) swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
    ls[i] = max(ls[j], ls[i]);
    fs[i] = min(fs[j], fs[i]);
}

int main () {
    scanf("%d %d %d", &n, &m, &p);
    p--;

    for (int i = 0; i <= n; i++) {
        scanf(" %c", str+i);
        ls[i] = fs[i] = uf[i] = i;
        wf[i] = 1;
    }

    ss = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == ')') {
            ss--;
            l[st[ss]] = i;
            l[i] = st[ss];
        } else {
            st[ss++] = i;
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d ", l[i]);
    printf("\n");

    int end = m-1;

    for (int i = 0; i < n; i++)
        if (ls[find(i)] == i)
            printf("%c", str[i]);
        else
            printf("x");
    printf("\n");

    for (int i = 0; i < m; i++) {
        scanf(" %c", &c);

        if (c == 'D') {
            if (str[p] == ')') p = l[p];
            int j = l[p];

            for (; p <= j; p = ls[find(p)])
                join(j, j+1);
        }

        if (c == 'L') {
            p = fs[find(p)]-1;
            assert(p);
        } else {
            p++;
        }

        p = ls[find(p)];
        if (p == m)
            p = fs[find(p)] - 1;

        for (int j = 0; j < n; j++)
            if (ls[find(j)] == j)
                printf("%c", str[j]);
            else
                printf("x");
        printf(" -> %d %d\n", p, i);
    }

    for (int i = 0; i < n; i++)
        if (ls[find(i)] == i)
            printf("%c", str[i]);
    printf("\n");
}
