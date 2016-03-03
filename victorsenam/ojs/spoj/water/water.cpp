#include <bits/stdc++.h>
using namespace std;

#define debug(...) {}

const int N = 10007;
const int M = 107;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int uf[N], wf[N];
int mat[M][M], n, m;
bool mk[N];
int ts, att, mr, res;
int srt[N];

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j) return;
    if (wf[i] < wf[j])
        swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

inline bool s_cmp (int i, int j) {
    return mat[i/m][i%m] < mat[j/m][j%m];
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &mat[i][j]);
                uf[i*m+j] = i*m+j;
                wf[i*m+j] = 1;
                srt[i*m+j] = i*m+j;
                mk[i*m+j] = 0;
            }
        }
        mk[n*m] = 1;
        uf[n*m] = n*m;
        wf[m*m] = 1;

        sort(srt, srt+n*m, s_cmp);
        res = att = mr = 0;

        int i = 0;
        for (int lv = 0; lv <= N && i < n*m; lv++) {
            for(; i < n*m && mat[srt[i]/m][srt[i]%m] == lv; i++) {
                int l = srt[i]/m; int c = srt[i]%m;
                att++;
                debug("(%d,%d)\n", l, c);
                mk[srt[i]] = 1;

                for (int k = 0; k < 4; k++) {
                    int nl = l + dx[k]; int nc = c + dy[k];
                    int vt = n*m;
                    if (nl >= 0 && nl < n && nc >= 0 && nc < m) {
                        vt = nl*m+nc;
                    }
                    if (find(srt[i]) == find(vt) || !mk[vt])
                        continue;

                    debug("(%d,%d)-(%d,%d)", l, c, nl, nc);
                    if (find(vt) == find(n*m)) {
                        mr += wf[find(srt[i])];
                        debug(" + %d", wf[find(srt[i])]);
                    } else if (find(srt[i]) == find(n*m)) {
                        mr += wf[find(vt)];
                        debug(" + %d", wf[find(vt)]);
                    }
                    debug("\n");
                    
                    join(vt, srt[i]);
                }
            }
            res += att - mr;
            debug("lv %d : %d - %d\n", lv, att, mr);
        }
        printf("%d\n", res);
    }
}
