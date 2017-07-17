#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii,pii> rrr;
#define pb push_back
#define fs first
#define sn second

const int N = 30;
int n, m;
char mat[N][N];
rrr bst;

void go (int ai, int aj, int bi, int bj, int & cc) {
    cc += (mat[ai][aj] == '.') + (mat[bi][bj] == '.');
    if (mat[ai][aj] == mat[bi][bj])
        cc = -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> n >> m) {
        bst = rrr(pii(N,N),pii(N,N));

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cin >> mat[i];
            for (int j = 0; j < m; j++)
                cnt += (mat[i][j] == '.');
        }

        // lin
        for (int l = 0; l + 1 < n; l++) {
            int cc = 0;
            for (int i = 0; cc != -1 && l + i < n && l - i - 1 >= 0; i++)
                for (int j = 0; cc != -1 && j < m; j++)
                    go(i+l,j, i-l-1,j, cc);

            if (cc == cnt)
                bst = min(bst, rrr(pii(l+1, 1), pii(l+1, m)));               
        }

        // col
        for (int c = 0; c + 1 < m; c++) {
            int cc = 0;
            for (int j = 0; cc != -1 && c + j < m && c - j - 1 >= 0; j++)
                for (int i = 0; cc != -1 && i < n; i++)
                    go(i,j+c, i,j-c-1, cc);

            if (cc == cnt)
                bst = min(bst, rrr(pii(1, c+1), pii(n, c+1)));
        }

        // diag princ cima
        for (int d = 0; d < m; d++) {
            int cc = 0;
            int ll = 0;
            for (int i = 0; cc != -1 && i < n && i + d < m; i++) {
                ll = i;
                for (int j = 1; cc != -1 && j + d < m && i + j < n; j++)
                    go(i,i+d+j, i+j,i+d, cc);
            }

            if (cc == cnt)
                bst = min(bst, rrr(pii(1,d+1), pii(ll+1,d+ll+1)));
        }

        // diag princ lado
        for (int d = 1; d < n; d++) {
            int cc = 0;
            int ll = 0;
            for (int j = 0; cc != -1; j++) {
                ll = j;
                for (int i = 0; cc != -1 && i < n; 
            }
        }
    }
}
