#include <bits/stdc++.h>

using namespace std;
 
const int N = 100;

int maxy, maxx;
int miny, minx;
int y, x;
int n, m;
char inp[N][N];

int main () {
    scanf("%d %d", &n, &m);

    miny = minx = INT_MAX;
    maxy = maxx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &inp[i][j]);
            if (inp[i][j] == '*') {
                miny = min(miny, i);
                minx = min(minx, j);
                maxy = max(maxy, i);
                maxx = max(maxx, j);
            }
        }
    }

    for (int i = miny; i <= maxy; i++) {
        for (int j = minx; j <= maxx; j++) {
            printf("%c", inp[i][j]);
        }
        printf("\n");
    }
}
