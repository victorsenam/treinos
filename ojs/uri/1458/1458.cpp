#include <bits/stdc++.h>

using namespace std;

const int N = 147;
const int P = 12;

char str[N];
double memo[N][P][P][P];
double res;
int vis[N][P][P][P];
int n;
int turn;
double distTo[P][P];

int getPosi (char a) {
    if (a == ' ')
        return 10;
    else if (a == '#')
        return 11;
    else if (a < 'a' || a > 'z')
        return 0;
    else if (a < 's')
        return (a-'a')/3 + 1;
    else if (a == 's')
        return 6;
    else if (a >= 't' && a <= 'v')
        return 7;
    else if (a >= 'w' && a <= 'z')
        return 8;
}

int typeTime (char a) {
    if (a > 'z' || a < 'a')
        return 1;

    int cnt = 1;
    int pos = getPosi(a);
    while (getPosi(--a) == pos)
        cnt++;
    return cnt;
}

double pd (int i, int lf, int rg, int ls) {
    if (i >= n)
        return 0.0;

    double & me = memo[i][lf][rg][ls];
    if (vis[i][lf][rg][ls] == turn)
        return me;
    vis[i][lf][rg][ls] = turn;

    int dest = getPosi(str[i]);
    me = 1200.0;
    
    if (dest == ls) {
        me = min(me, pd(i, 11, rg, 11) + distTo[lf][11]);
        me = min(me, pd(i, lf, 11, 11) + distTo[rg][11]);
    } else {
        me = min(me, pd(i+1, dest, rg, dest) + distTo[lf][dest]);
        me = min(me, pd(i+1, lf, dest, dest) + distTo[rg][dest]);
    }

    return me;
}

int main () {
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            distTo[i][j] = (sqrt((double)((i/3)-(j/3))*((i/3)-(j/3)) + (double)((i%3)-(j%3))*((i%3)-(j%3))));


    while (scanf(" %[a-z ]s", str) != EOF) {
        n = strlen(str);
        turn++;
        int pres = 0;
        res = pd(0, 3, 5, 11);
        res /= 30.0;

        for (int i = 0; i < n; i++) {
            pres += typeTime(str[i]);
            if (i && getPosi(str[i]) == getPosi(str[i-1]))
                pres++;
        }

        printf("%.2lf\n", res + pres*0.2);
    }
}
