#include <bits/stdc++.h>

using namespace std;

const int W = 101;
const int N = 2*W*W + 3;
const int M = W*W*4 + 2*W + 3;

const int di[4] = {1, -1, 0, 0};
const int dj[4] = {0, 0, 1, -1};

// 0 |- w*h         esq
// w*h |- 2*w*h     dir
// 2*w*h            src
// 2*w*h+1          snk
int mat[W][W];
int hd[N], nx[M], to[M], cap[M], flx[M], es;
int h, w;

inline bool isVal (int i, int j, int v) {
    if (i < 0 || i >= h)
        return 0;
    if (j < 0 || j >= w)
        return 0;
    return (mat[i][j] != v);
}

int main () {
    scanf("%d %d", &h, &w);

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            scanf("%d", &mat[i][j]);
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            connect(i*w+j, 2*w*h);
            connect(w*h + i*w+j, 2*w*h+1);
            for (int k = 0; k < 4; k++) {
                if (isVal(i+di[k], j+dj[k], mat[i][j])
                    connect(i*w+j, w*h + (i+di[k])*w+(j+dj[k]));
            }
        }
    }
}
