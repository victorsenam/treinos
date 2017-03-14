#include <bits/stdc++.h>

using namespace std;

#define F 10
#define H 100
#define N 101
#define S 3335

struct posi {
    int floor;
    int row;
    int col;
};

int mov[2] = {1, -1};
char tab[F][H][H];
int dist[F][H][H];
pair<posi, int> peep[N];
int memo[N][S];
queue<pair<posi, int> > q;
int t;
posi aux;
posi next;
int a;
int l, h, w, n, s;

int pd (int its, int tim) {
    int a;
    if (its < 0 || tim <= 0) return 0;
    if (memo[its][tim] != -1) return memo[its][tim];

    a = dist[peep[its].first.floor-1][peep[its].first.row-1][peep[its].first.col-1];

    memo[its][tim] = max(pd(its-1, tim), pd(its-1, tim-a) + (tim >= a)*peep[its].second);
 //   printf("%d %d -> %d\n", its, tim, memo[its][tim]);
    return memo[its][tim];
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d %d", &l, &h, &w, &n, &s);
        s /= 3;
        for (int k = 0; k < l; k++) {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    scanf(" %c", &tab[k][i][j]);
                    dist[k][i][j] = INT_MAX;
                    if (tab[k][i][j] == 'S') {
                        aux.floor = k;
                        aux.row = i;
                        aux.col = j;
                        q.push(make_pair(aux, 0));
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &aux.floor, &aux.row, &aux.col, &a);
            peep[i].first = aux;
            peep[i].second = a;
        }

        while (!q.empty()) {
            aux = q.front().first;
            a = q.front().second;
            q.pop();

            if (aux.row >= h || aux.row < 0 || aux.col >= w || aux.col < 0 || dist[aux.floor][aux.row][aux.col] <= a || tab[aux.floor][aux.row][aux.col] == 'X') continue;
            dist[aux.floor][aux.row][aux.col] = a;

            for (int i = 0; i < 4; i++) {
                next = aux;
                if (i/2) next.row += mov[i%2];
                else next.col += mov[i%2];
                q.push(make_pair(next, a+1));
            }
            
            if (tab[aux.floor][aux.row][aux.col] == '.' || !a) continue;
            
            next = aux;
            if (tab[aux.floor][aux.row][aux.col] == 'U') next.floor++;
            else if (tab[aux.floor][aux.row][aux.col] == 'D') next.floor--;

            q.push(make_pair(next, a+1));
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j <= s; j++)
                memo[i][j] = -1;

 //       for (int i = 0; i < n; i++) printf("(%d,%d) ", dist[peep[i].first.floor-1][peep[i].first.row-1][peep[i].first.col-1], peep[i].second);
 //       printf("\n");
 //       for (int i = 0; i < n; i++) printf("(%d,%d) ", ks[i].first, ks[i].second);

        printf("%d\n", pd(n-1, s));
    }
}
