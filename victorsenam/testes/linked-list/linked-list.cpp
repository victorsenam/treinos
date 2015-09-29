#include <bits/stdc++.h>

using namespace std;

const int N = 100007;
const int M = 1000007;

int head[N], to[M], next[M], es;
int n, m;
int a, b;

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        head[i] = -1;
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        next[es] = head[a]; head[a] = es; to[es++] = b;
        next[es] = head[b]; head[b] = es; to[es++] = a;
    }

    for (int i = 0; i < n; i++) {
        printf("%d: ", i);
        for (int ed = head[i]; ed != -1; ed = next[ed])
            printf("%d ", to[ed]);
        printf("\n");
    }
}
