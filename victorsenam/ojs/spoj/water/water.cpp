// ERRADO

#include <bits/stdc++.h>
using namespace std;

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
    uf[i] = find(uf[i]);
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

        for (int i = 0; i < n*m; i++) {
            int l = srt[i]/m; int c = srt[i]%m;
            if (i && mat[l][c] != mat[srt[i-1]/m][srt[i-1]%m]) {
                res += att - mr;
            }
            att++;
            mk[srt[i]] = 1;

            for (int k = 0; k < 4; k++) {
                int nl = l + dx[k]; int nc = c + dy[k];
                int vt = n*m;
                if (nl > 0 && nl < n && nc > 0 && nc < m) {
                    vt = nl*m+nc;
                }
                if (find(srt[i]) == find(vt) || !mk[vt])
                    continue;

                if (find(vt) == find(n*m))
                    mr += wf[find(srt[i])];
                
                join(vt, srt[i]);
            }
        }
        printf("%d\n", res);
    }
}
