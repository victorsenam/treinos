#include <bits/stdc++.h>

using namespace std;

int w, d;
int x, y;
int ox, oy;
char c;
double tx, ty;

int main ( ){ 
    scanf("%d %d", &w, &d);
    scanf("%d %d", &x, &y);
    scanf("%d %d", &ox, &oy);

    while (scanf(" %c", &c) != EOF) {
        if (c == 'L') {
            tx += x;
            x = 0;
        } else if (c == 'R') {
            tx += (w - x);
            x = w;
        } else if (c == 'F') {
            ty += y;
            y = 0;
        } else {
            ty += (d - y);
            y = d;
        }
    }

    tx += max(x-ox,ox-x);
    ty += max(y-oy,oy-y);

    printf("%.4lf\n", sqrt(tx*tx+ty*ty));
}
