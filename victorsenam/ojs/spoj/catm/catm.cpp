#include <cstdio>

using namespace std;

typedef struct {int l; int c;} pos;

int n, m, t, d;
pos r, g1, g2, end;

int dist (pos a, pos b) {
    int res;
    if (a.l > b.l) res = a.l - b.l;
    else res = b.l - a.l;

    if (a.c > b.c) res += a.c - b.c;
    else res += b.c - a.c;

    return res;
}

int main () {
    scanf("%d %d %d", &m, &n, &t);
    while (t--) {
        scanf("%d %d %d %d %d %d", &(r.l), &(r.c), &(g1.l), &(g1.c), &(g2.l), &(g2.c));

        end.l = r.l;
        end.c = 1;
        d = dist(r, end);
        if (d < dist(g1, end) && d < dist(g2, end)) {
            printf("YES\n");
            continue;
        }
        end.l = 1;
        end.c = r.c;
        d = dist(r, end);
        if (d < dist(g1, end) && d < dist(g2, end)) {
            printf("YES\n");
            continue;
        }
        end.l = r.l;
        end.c = m;
        d = dist(r, end);
        if (d < dist(g1, end) && d < dist(g2, end)) {
            printf("YES\n");
            continue;
        }
        end.l = n;
        end.c = r.c;
        d = dist(r, end);
        if (d < dist(g1, end) && d < dist(g2, end)) {
            printf("YES\n");
            continue;
        }
        printf("NO\n");
    }
}
