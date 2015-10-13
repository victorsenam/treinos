#include <bits/stdc++.h>

using namespace std;

const int N = 2003;
const int M = 200003;

int n, m;
int hd[N], nx[M], to[M], es;
int a, b;

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        hd[i] = -1;
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        to[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        to[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }
}
