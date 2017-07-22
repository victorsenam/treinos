#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e3+7;

int ts, n;
int lis[N][N];
int sz[N];
int rep[N];
bool lala[N][N];
int visi[N][N], turn;

bool isvis (int u, int v) {
    if (u > v) swap(u,v);
    return (visi[u][v] == turn);
}

void get (int & n) {
    char c;
    while(isspace(c = getchar()));
    n = c - '0';
    while(!isspace(c = getchar()))
        n = (n << 3) + (n << 1) + (c - '0');
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    get(ts);
    while (ts--) {
        vector<pii> res;
        get(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                lala[i][j] = 0;
                get(lis[i][j]);
                lis[i][j]--;
            }
            rep[i] = i;
            sz[i] = n;
        }

        int cmps = n;

        while (cmps > 1) {
            turn++;
            vector<pii> edg;

            for (int u = 0; u < n; u++) {
                if (u != rep[u]) continue;
                int i = 0;
                for (int j = 0; j < sz[u]; j++) {
                    if (rep[lis[u][j]] != u && !isvis(u,lis[u][j]))
                        lis[u][i++] = lis[u][j];
                }
                sz[u] = i;
            }

            for (int u = 0; u < n; u++) {
                if (u != rep[u]) continue;

                int v = rep[lis[u][0]];

                pii aux(u,v);
                if (u > v)
                    swap(aux.first, aux.second);
                
                if (!lala[aux.first][aux.second]) {
                    edg.push_back(aux);
                    lala[aux.first][aux.second] = 1;
                }
            }

            for (pii aux : edg) {
                int u = aux.first;
                int v = aux.second;

                int a = u;
                for (int j = 0; j < sz[u]; j++) {
                    a = lis[u][j];
                    if (rep[a] != v) continue;
                    break;
                }

                int b = v;
                for (int j = 0; j < sz[v]; j++) {
                    b = lis[v][j];
                    if (rep[b] != u) continue;
                    break;
                }

                cout << a+1 << " " << b + 1 << endl;
            }

            for (pii aux : edg) {
                cmps--;
                int c = rep[aux.second];
                for (int i = 0; i < n; i++)
                    if (rep[i] == c)
                        rep[i] = rep[aux.first];
            }
        }

        for (pii aux : res)
            cout << aux.first + 1 << " " << aux.second + 1 << endl;
        cout << endl;
    }
}
