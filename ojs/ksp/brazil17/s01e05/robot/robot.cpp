#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1123;
int h[N][N];
int seen[N][N], tempo;
string s;
bool dfs(int i, int j, int di, int dj, bool any=false) {
    if(!any && (i > di || j > dj)) return false;
    if(any && (i > di || j > dj)) return true;
    if(h[i][j]) return false;
    if(i == di && j == dj) return true;
    seen[i][j] = tempo;
    if(seen[i][j + 1] != tempo) {
        s.pb('0');
        if(dfs(i, j + 1, di, dj, any)) return true;
        s.pop_back();
    }
    if(seen[i + 1][j] != tempo) {
        s.pb('1');
        if(dfs(i + 1, j, di, dj, any)) return true;
        s.pop_back();
    }
    return false;
}

char g[N][N];
pii p[N][N];
#define fst first
#define snd second

int main () {
    int i, n, k, j;
    ios::sync_with_stdio(0);
    cin.tie(0);
    scanf("%d %d", &n, &k);
    for(i = 0; i < n; i++)
        scanf("%s", g[i]);
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            h[i][j] = (g[i][j] == 'X');
    g[0][0] = '.';
    vector<string> sols;
    tempo++;
    queue<pii> q;
    q.push(pii(0, 0));
    while(!q.empty()) {
        pii x = q.front(); q.pop();
        i = x.fst; j = x.snd;
        if(i >= n || j >= n) {
            string s;
            while(i || j) {
                if(p[i][j].fst == i) s.pb('0');
                else s.pb('1');
                x = p[i][j];
                i = x.fst;
                j = x.snd;
            }
            reverse(s.begin(), s.end());
            sols.pb(s);
            break;
        }
        if(!seen[i][j + 1] && g[i][j + 1] != 'X') {
            seen[i][j + 1] = 1;
            p[i][j + 1] = x;
            q.push(pii(i, j + 1));
        }
        if(!seen[i + 1][j] && g[i + 1][j] != 'X') {
            seen[i + 1][j] = 1;
            p[i + 1][j] = x;
            q.push(pii(i + 1, j));
        }
    }
    for(int di = 0; di < n && di <= k; di++)
        for(int dj = 0; dj < n && dj + di <= k; dj++) {
            if(!di && !dj) continue;
            for(int i = 0; i <= di; i++)
                for(int j = 0; j <= dj; j++)
                    h[i][j] = (g[i][j] == 'X');
            for(int k = 1; k * di < n && k * dj < n; k++)
                for(int i = k * di, oi = k * di; i <= (k + 1) * di && i < n; i++)
                    for(int j = k * dj, oj = k * dj; j <= (k + 1) * dj && j < n; j++)
                        if(g[i][j] == 'X') {
                            h[i - oi][j - oj] = 1;
                        }
            tempo++;
            s.clear();
            if(dfs(0, 0, di, dj))
                sols.pb(s);
        }
    printf("%s\n", min_element(sols.begin(), sols.end(), [](string a, string b) { return (a.size() != b.size()? a.size() < b.size() : a < b); })->c_str());
}

