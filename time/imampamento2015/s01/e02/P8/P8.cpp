#include <bits/stdc++.h>

using namespace std;

#define N 14
#define J 3

typedef int num;

bool visi[N][N][N][N][J][J][J][J];
double memo[N][N][N][N][J][J][J][J];
int t, oc, od, oh, os;

inline double prob (int qtd, int tot) {
    if (qtd <= 0) return 0.0;
    return (double)qtd / (double)tot;
}

bool possi (num c, num d, num h, num s, num jc, num jd, num jh, num js) {
    int j = 2 - jc - jd - jh - js;
    j -= max(oc-13-jc, 0);
    j -= max(od-13-jd, 0);
    j -= max(oh-13-jh, 0);
    j -= max(os-13-js, 0);
    
    if (j < 0) 
        return 0;
    return 1;
}

double pd (num c, num d, num h, num s, num jc, num jd, num jh, num js) {
    if (visi[c][d][h][s][jc][jd][jh][js])
        return memo[c][d][h][s][jc][jd][jh][js];

    visi[c][d][h][s][jc][jd][jh][js] = 1;
    double res = 0.0;
    double pb;

    if (c + jc >= oc && d + jd >= od && h + jh >= oh && s + js >= os)
            return 0.0;

    double mini = 60.0;
    pb = prob(13 - c, 54-c-d-h-s-jc-jd-jh-js);
    if (pb > 0) {
        res += pb*pd(c+1, d, h, s, jc, jd, jh, js);
    }
    if (possi(c, d, h, s, jc+1, jd, jh, js)) {
        mini = min(mini, pd(c, d, h, s, jc+1, jd, jh, js));
    }

    pb = prob(13 - d, 54-c-d-h-s-jc-jd-jh-js);
    if (pb > 0) {
        res += pb*pd(c, d+1, h, s, jc, jd, jh, js);
    }
    if (possi(c, d, h, s, jc, jd+1, jh, js)) {
        mini = min(mini, pd(c, d, h, s, jc, jd+1, jh, js));
    }

    pb = prob(13 - h, 54-c-d-h-s-jc-jd-jh-js);
    if (pb > 0) {
        res += pb*pd(c, d, h+1, s, jc, jd, jh, js);
    }
    if (possi(c, d, h, s, jc, jd, jh+1, js)) {
        mini = min(mini, pd(c, d, h, s, jc, jd, jh+1, js));
    }

    pb = prob(13 - s, 54-c-d-h-s-jc-jd-jh-js);
    if (pb > 0) {
        res += pb*pd(c, d, h, s+1, jc, jd, jh, js);
    }
    if (possi(c, d, h, s, jc, jd, jh, js+1)) {
        mini = min(mini, pd(c, d, h, s, jc, jd, jh, js+1));
    }

    res += prob(2-jc-jd-jh-js, 54-c-d-h-s-jc-jd-jh-js)*mini;
    res += 1.0;
    memo[c][d][h][s][jc][jd][jh][js] = res;
 //   printf("%d %d %d %d %d %d %d %d -> %.3f\n", c, d, h, s, jc, jd, jh, js, res);
    return res;
}

int main () {
    scanf("%d", &t);

    for (int c = 1; c <= t; c++) {
        scanf("%d %d %d %d", &oc, &od, &oh, &os);
//        printf("%d %d %d %d", oc, od, oh, os);

        for (int i1 = 0; i1 < N; i1++) {
        for (int i2 = 0; i2 < N; i2++) {
        for (int i3 = 0; i3 < N; i3++) {
        for (int i4 = 0; i4 < N; i4++) {
            for (int j1 = 0; j1 < J; j1++) {
            for (int j2 = 0; j2 < J; j2++) {
            for (int j3 = 0; j3 < J; j3++) {
            for (int j4 = 0; j4 < J; j4++) {
                memo[i1][i2][i3][i4][j1][j2][j3][j4] = 0;
                visi[i1][i2][i3][i4][j1][j2][j3][j4] = 0;
        }}}}}}}}

        if (possi(0,0,0,0,0,0,0,0))
            printf("Case %d: %.3f\n", c, pd(0, 0, 0, 0, 0, 0, 0, 0));
        else
            printf("Case %d: -1.000\n", c);
    }
}
