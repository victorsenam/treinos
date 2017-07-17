#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, string> cand;
#define pb push_back

const int N = 1e3+7;
const int inf = N;

int n;
char str[N][10];
int dist[2][N];

bool isadj (int i, int j) {
    int df = 0;
    for (int k = 0; str[i][k]; k++) {
        if (str[i][k] != str[j][k]) {
            if (df)
                return 0;
            df++;
        }
    }

    return (df == 1);
}

string getadj (int i, int j) {
    string res = str[i];
    int df = 0;
    for (int k = 0; str[i][k]; k++) {
        if (str[i][k] != str[j][k]) {
            if (df == 0) {
                if (str[i][k] > str[j][k]) swap(i,j);
                res[k] = str[i][k];
                df++;
            } else if (df == 1) {
                res[k] = str[j][k];
                df++;
            } else {
                return "0";
            }
        }
    }

    return res;
}

void bfs (int k) {
    queue<int> qu;

    for (int i = 0; i < n; i++)
        dist[k][i] = inf;

    qu.push(k);
    dist[k][k] = 0;

    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();

        for (int i = 0; i < n; i++) {
            if (dist[k][i] <= dist[k][u] + 1) continue;
            if (!isadj(u,i)) continue;

            dist[k][i] = dist[k][u] + 1;
            qu.push(i);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> n) {
        for (int i = 0; i < n; i++)
            cin >> str[i];

        for (int k = 0; k < 2; k++) {
            bfs(k);
        }

        cand bst(dist[0][1], "0");

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (isadj(i,j)) continue;
                
                cand cur;
                cur.second = getadj(i,j);
                if (cur.second == "0") continue;
                cur.first = dist[0][i] + dist[1][j] + 2;
                
                if (cur < bst)
                    bst = cur;
            }
        }

        if (bst.first == inf)
            bst.first = -1;
        cout << bst.second << endl;
        cout << bst.first << endl;
    }
}
