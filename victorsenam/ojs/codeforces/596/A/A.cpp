#include <bits/stdc++.h>

using namespace std;

typedef int num;

int n;
pair<int, int> pos[4];
int w, h;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &pos[i].first, &pos[i].second);
    }

    w = 0;
    h = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            w = max(w, abs(pos[i].first - pos[j].first));
            h = max(h, abs(pos[i].second - pos[j].second));
        }
    }

    if (w == 0 || h == 0)
        printf("-1\n");
    else
        printf("%d\n", h*w);
}
