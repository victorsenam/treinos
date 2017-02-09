#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const double pi = acos(-1.0);
typedef complex<double> cpx;

const int N = 5e4+7;

vector<cpx> aux[3];
int p[4*N];

// XXX assumes v.size() is power of 2
// if inv is true, runs inverse DFT
void fft (vector<cpx> & ans, vector<cpx> & a, bool inv) {
    int n = a.size();
    assert(!(n&(n-1)));

    for (int i = 0; i < n; i++)
        ans[i] = a[p[i]];

    for (int sz = 1; sz < n; sz <<= 1) {
        const cpx root(cos(pi / sz), sin((1. - inv - inv) * pi / sz));
        for (int j = 0; j < n; j += (sz << 1)) {
            cpx w = 1;
            for (int i = 0; i < sz; i++) {
                const cpx t = w * ans[i + j + sz];
                ans[i + j + sz] = ans[i + j] - t;
                ans[i + j] += t;
                w *= root;
            }
        }
    }

    if (inv)
        for (int i = 0; i < n; i++)
            ans[i] /= n;
}

int n;
char str[2][N];
int res[N][5][5];
vector<cpx> v[2];

int memo[(1<<5)];
int ms[(1<<5)];

int main () {
    scanf(" %s %s", str[0], str[1]);
    n = strlen(str[0]);
    int sz = 2*n;
    while (sz&(sz-1)) sz += (sz&-sz); // geq power of 2
    v[0].resize(sz, 0);
    v[1].resize(sz, 0);

    for (int i = 1; i < sz; i++)
        p[i] = (p[i >> 1] >> 1) | ((i&1) ? (sz >> 1) : 0);
    for (int i = 0; i < 3; i++)
        aux[i].resize(sz, 0);

    for (char a = 'A'; a <= 'E'; a++) {
        for (int i = 0; i < n; i++)
            v[0][i] = v[0][i+n] = (str[0][i] == a);
        fft(aux[0], v[0], 0);
        for (char b = 'a'; b <= 'e'; b++) {
            for (int i = 0; i < n; i++)
                v[1][n-i-1] = (str[1][i] == b);
            fft(aux[1], v[1], 0);
            for (int i = 0; i < sz; i++)
                aux[1][i] *= aux[0][i];
            fft(aux[2], aux[1], 1);

            for (int i = 0; i < n; i++)
                res[i][a-'A'][b-'a'] = (aux[2][i+n-1].real() + 0.2);
        }
    }

    for (int mask = 0; mask < (1<<5)-1; mask++)
        ms[mask] = mask;
    sort(ms, ms+(1<<5)-1, [] (int i, int j) {
        return (__builtin_popcount(i) > __builtin_popcount(j));
    });

    int ans = 0;

    for (int k = 0; k < n; k++) {
        for (int _pp = 0; _pp < (1<<5)-1; _pp++) {
            int mask = ms[_pp];
            int i = __builtin_popcount(mask);
                
            memo[mask] = 0;

            for (int j = 0; j < 5; j++) {
                if ((1<<j)&mask) continue;

                memo[mask] = max(memo[mask], memo[mask|(1<<j)] + res[k][i][j]);
            }
        }
        ans = max(ans, memo[0]);
    }

    printf("%d\n", n-ans);
}
