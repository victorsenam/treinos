#include <bits/stdc++.h>
#include <cmath>

using namespace std;

struct hole {
    int x, y, r;
    int o, h;
};

int t;
int w, l, b, org;
int d;
vector<hole> hs;
vector<int> ht, hb;
hole h;

int tang (int x, int y) {
    return ceil(sqrt(x*x + y*y));
}

int abs (int x) {
    if (x < 0) return -x;
    return x;
}

void connect(int a, int b) {
    int aux;
//    printf("-- %d %d\n", a, b);

    while (hs[a].o != a) a = hs[a].o;
    while (hs[b].o != b) b = hs[b].o;

    if (a == b) return;
    if (hs[a].h < hs[b].h) {
        aux = a;
        a = b;
        b = aux;
    }

    hs[b].o = a;
    hs[a].h = max(hs[b].h+1, hs[a].h);
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d", &w, &l, &b);
        hs.clear();
        ht.clear();
        hb.clear();

        h.x = h.y = h.r = h.o = 0;
        h.h = 1;
        hs.push_back(h);
        h.o = 1;
        hs.push_back(h);


        for (int i = 2; i < b+2; i++) {
            scanf("%d %d %d", &h.x, &h.y, &h.r);
            h.o = i;
            h.h = 1;
            hs.push_back(h);

            if (h.x - h.r <= 0)
                connect(0, i);
            if (h.x + h.r >= w) 
                connect(1, i);
            for (int j = 2; j < i; j++)
                if (tang(hs[i].x-hs[j].x, hs[i].y-hs[j].y) <= hs[i].r + hs[j].r) connect(i, j);
        }

/*
        for (int i = 0; i < b+2; i++) 
            printf("%d ", hs[i].o);
        printf("\n");
*/

        // compress path to top and bottom
        while (hs[0].o != 0) {
            int a = hs[0].o;
            hs[0].o = hs[a].o;
            hs[a].o = 0;
        }
        while (hs[1].o != 1) {
            int a = hs[1].o;
            hs[1].o = hs[a].o;
            hs[a].o = 1;
        }

        if (hs[0].o == 1) {
            printf("Bridge already split\n");
            continue;
        }

/*
        for (int i = 0; i < b+2; i++) 
            printf("%d ", hs[i].o);
        printf("\n");
*/

        for (int i = 2; i < b+2; i++) {
            int a = i;
            while (hs[a].o != a) a = hs[a].o;
            if (a == 0) ht.push_back(i);
            else if (a == 1) hb.push_back(i);
        }

        int minB = w;
        for (int i = 0; i < ht.size(); i++) {
            minB = min(minB, w - hs[ht[i]].x - hs[ht[i]].r);
 //           printf("%d %d %d\n", hs[ht[i]].x, hs[ht[i]].y, hs[ht[i]].r);
            for (int j = 0; j < hb.size(); j++) {
   //             printf("\t%d %d %d\n", hs[hb[j]].x, hs[hb[j]].y, hs[hb[j]].r);
                if (!i) minB = min(minB, hs[hb[j]].x - hs[hb[j]].r);
                
                minB = min(minB, tang(hs[ht[i]].x - hs[hb[j]].x, hs[ht[i]].y - hs[hb[j]].y) - hs[ht[i]].r - hs[hb[j]].r);
            }
        }

        printf("%d\n", minB/2 + minB%2);
    }
}
