#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int n, m;
int a[N], b[N];
int x, y, t;

int main () {
    freopen("knockout.in", "r", stdin);
    freopen("knockout.out", "w", stdout);
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf("%d %d", a+i, b+i);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &t);

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            bool ch = 0;
            int in = a[i];
            int fi = b[i];
            if (in > fi) {
                ch = 1;
                swap(in, fi);
            }
            int dis = fi-in;
            int mov = t%(dis<<1);

            if (mov >= dis) {
                ch = !ch;
                mov -= dis;
            }
            
            if (ch)
                mov = dis-mov;
            
            int pos = in+mov;

            if (pos >= x && pos <= y)
                cnt++;
        }
        printf("%d\n", cnt);
    }
    
}
