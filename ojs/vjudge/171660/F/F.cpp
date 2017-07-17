#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const ll modn = 1000000009;
inline ll mod(ll x) { return x % modn; }

const int N = 256;
int m;


int di[] = {2, 1, 2, 1, -2, -1, -2, -1};
int dj[] = {1, 2, -1, -2, 1, 2, -1, -2};

vector<int> ind;

inline int id(int i, int j) { return i * m + j; }

inline bool ok(int bm) {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < m; j++)
            if((bm >> id(i, j)) & 1)
                for(int d = 0; d < 8; d++) {
                    int ni = i + di[d];
                    int nj = j + dj[d];
                    if(ni < 0 || ni >= 3 || nj < 0 || nj >= m) continue;
                    if((bm >> id(ni, nj)) & 1) return false;
                }
    return true;
}

inline void mult(ll A[N][N], ll B[N][N], ll C[N][N], int n) {
    for(int i : ind)
        for(int j : ind) {
            C[i][j] = 0;
            for(int k : ind)
                C[i][j] = mod(C[i][j] + A[i][k] * B[k][j]);
        }
}

inline void cp(ll A[N][N], ll B[N][N], int n) {
    for(int i : ind)
        for(int j : ind)
            B[i][j] = A[i][j];
}

ll aux[N][N];
void fexp(ll A[N][N], ll p, ll B[N][N], int n) {
    for(int i : ind)
        for(int j : ind)
            B[i][j] = (i == j);
    for(; p; p >>= 1) {
        if(p & 1) {
            mult(B, A, aux, n);
            cp(aux, B, n);
        }
        mult(A, A, aux, n);
        cp(aux, A, n);
    }
}

ll M[N][N], ans[N][N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    int i, j, n;

    while(t--) {
        memset(M, 0, sizeof M);
        cin >> m >> n;
        ind.clear();
        for(i = 0; i < (1 << (2 * m)); i++)
            if(ok(i))
                ind.pb(i);
        for(int i : ind)
            for(j = 0; j < (1 << m); j++)
                if(ok(i | (j << (2 * m))))
                    M[i][(i >> m) | (j << m)]++;
        fexp(M, n, ans, ind.size());
        ll r = 0;
        for(int i : ind)
            r += ans[0][i];
        printf("%lld\n", mod(r));
    }
}
