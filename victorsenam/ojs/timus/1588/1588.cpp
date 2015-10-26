#include <bits/stdc++.h>

using namespace std;

const int N = 10007;

const int N = 307;

struct pos {
    int x, y;
};

pos anc;
int n;
pos v[N], u[N];
int pa[N], pl[N];

inline double dist (pos a, pos b)
{ return sqrt( (double) ( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) ) ); }

inline int cross (pos a, pos b)
{ return a.x*b.y - a.y*b.x; }

inline pos diff (pos a, pos b) {
    pos res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
}

bool cmp_lex (pos a, pos b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool cmp_ang (pos a, pos b) {
    return cross(diff(anc, a), diff(anc, b)) < 0;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &v[i].x, &v[i].y);

    sort(v, v+n, cmp_lex);
    
    double res = 0.0;

    for (int i = 0; i < n-1; i++) {
        for (int j = i; j < n; j++)
            u[j] = v[j];

        anc = v[i];
        sort(u+i+1, u+n, cmp_ang);

        double mini = dist(anc, u[i+1]);
        for (int j = i+2; j < n; j++) {
            if (cmp_ang(u[j-1], u[j])) {
                res += mini;
                mini = dist(anc, u[j]);
            } else {
                mini = min(dist(anc, u[j]), mini);
            }
        }
        res += mini;
    }

    printf("%.0lf\n", round(res));
}
