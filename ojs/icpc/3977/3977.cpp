#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

#define N 500

int t, h, w;
num d;
num tab[N][N];
int vis[N][N];

class hcomp {
public:
    bool operator() (pair<int, int> a, pair<int, int> b) {
        return tab[a.first][a.second] < tab[b.first][b.second];
    }
};

priority_queue<pair<int, int>, vector<pair<int, int> >, hcomp> pq;
queue<pair<int, int> > q;
pair<int, int> pos;
num hi, lo, at;
int eqs, turn;
bool ispeak, isborder;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %lld", &h, &w, &d);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                scanf("%lld", &tab[i][j]);
                pq.push(make_pair(i, j));
                vis[i][j] = 0;
            }
        }

        int cnt = 0;
        turn = 0;
        while (!pq.empty()) {
            pos = pq.top();
            pq.pop();
            hi = tab[pos.first][pos.second];
            if (vis[pos.first][pos.second]) continue;

            if (hi < d) break;
            lo = hi - d;

            q.push(pos);
            ispeak = 1;
            turn++;
            eqs = 0;

            while (!q.empty()) {
                pos = q.front();
                q.pop();

                if (vis[pos.first][pos.second] == turn) continue;

                at = tab[pos.first][pos.second];                
                isborder = vis[pos.first][pos.second];

                vis[pos.first][pos.second] = turn;

                if (at == hi) eqs++;

                if (at > hi || (at > lo && isborder)) ispeak = 0;
                if (isborder || at <= lo) continue;

                for (int i = 0; i < 4; i++) {
                    pos.first += (!i) - (i==1) - (i==2) + (i==3);
                    pos.second += (i==1) - (i==2) - (i==3);
                    if (pos.first >= 0 && pos.first < h && pos.second >= 0 && pos.second < w) q.push(pos);
                }
            }

            cnt += eqs*ispeak;
        }

        printf("%d\n", cnt);
    }
}
