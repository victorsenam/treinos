#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int v[N];
int n;
int esq[N], dir[N];
int sume, sumd, best, att;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", v+i);

    esq[0] = sume = v[0];
    dir[n-1] = sumd = v[n-1];
    best = att = max(v[0], 0);
    for (int i = 1; i < n; i++) {
        sume += v[i];
        sumd += v[n-i-1];
        esq[i] = max(esq[i-1], sume);
        dir[n-i-1] = max(dir[n-i], sumd);

        att = max(att+v[i], 0);
        best = max(att, best);
    }

    for (int i = 1; i < n; i++)
        best = max(best, esq[i-1]+dir[i]);
    
    printf("%d\n", best);
}
