#include <bits/stdc++.h>

using namespace std;

#define N 200002

char sta[N], stb[N];
int atob[256][256], isa[256];
int n, h, maxi, sa, sb;
vector<int> d;

int main () {
    scanf("%d", &n);
    scanf(" %s %s", sta, stb);

    sa = sb = -1;
    maxi = 0;

    for (int i = 0; i < 256; i++) {
        isa[i] = -1;
        for (int j = 0; j < 256; j++) {
            atob[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (sta[i] == stb[i]) continue;
        h++;
        atob[sta[i]][stb[i]] = i;
        isa[sta[i]] = i;
        d.push_back(i);
    }

    for (vector<int>::iterator it = d.begin(); maxi < 2 && it != d.end(); it++) {
        if (atob[stb[*it]][sta[*it]] != -1) {
            maxi = 2;
            sa = *it;
            sb = atob[stb[*it]][sta[*it]];
        } else if (isa[stb[*it]] != -1) {
            maxi = 1;
            sa = *it;
            sb = isa[stb[*it]];
        }
    }

    if (maxi == 0) printf("%d\n%d %d\n", h, -1, -1);
    else printf("%d\n%d %d\n", h-maxi, sa+1, sb+1);
}
