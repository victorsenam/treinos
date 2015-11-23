#include <bits/stdc++.h>

using namespace std;

int x[2], y[2];
int cx, cy;
int gx[2], gy[2];
set<int> sx, sy;

void fail () {
    printf("NO\n");
    exit(0);
}

int main () {

    for (int i = 0; i < 4; i++) {
        scanf("%d %d %d %d", x, y, x+1, y+1); 
        sx.insert(x[0]);
        sx.insert(x[1]);
        sy.insert(y[0]);
        sy.insert(y[1]);

        if (x[0] != x[1] && y[0] != y[1])
            fail();
        else if (y[0] != y[1]) {
            cy++;
            if (cy > 2)
                fail();
            
            if (y[0] > y[1])
                swap(y[0], y[1]);

            if (cy == 1) {
                gy[0] = y[0];
                gy[1] = y[1];
            } else {
                if (gy[0] != y[0] || gy[1] != y[1])
                    fail();
            }
        } else if (x[0] != x[1]) {
            cx++;
            if (cx > 2)
                fail();
            
            if (x[0] > x[1])
                swap(x[0], x[1]);

            if (cx == 1) {
                gx[0] = x[0];
                gx[1] = x[1];
            } else {
                if (gx[0] != x[0] || gx[1] != x[1])
                    fail();
            }
        } else
            fail(); // point
    }

    if (sx.size() != 2 || sy.size() != 2)
        fail();

    printf("YES\n");
}
