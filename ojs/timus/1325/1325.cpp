#include <bits/stdc++.h>

using namespace std;

const int N = 500;
const int mi[8] = {0, 0, 1, -1, -1, -1, 1, 1};
const int mj[8] = {1, -1, 0, 0, -1, 1, -1, 1};

struct edge {
    int i, j;
    int b, d;
    bool operator < (const edge & a) const {
        if (b == a.b)
            return d > a.d;
        return b > a.b;
    }
};

int n, m;
priority_queue<edge> pq;
edge ini, fim;
bool visi[N][N];
char mat[N][N];

inline bool isVal (edge & a) {
    return (a.i >= 0 && a.i < n && a.j >= 0 && a.j < m);
}

int main () {
    scanf("%d %d %d %d %d %d", &n, &m, &ini.i, &ini.j, &fim.i, &fim.j);
    ini.i--; ini.j--; fim.i--; fim.j--;
    ini.d = 1;
    ini.b = 0;
    fim.d = INT_MAX;
    pq.push(ini);

    for (int i = 0; i < n; i++)
        scanf(" %s", mat[i]);

    while (!pq.empty()) {
        edge att = pq.top();
        pq.pop();
        if (visi[att.i][att.j])
            continue;
        visi[att.i][att.j] = 1;

        if (fim.i == att.i && fim.j == att.j) {
            fim = att;
            break;
        }

        for (int k = 0; k < 8; k++) {
            edge nx = att;
            nx.i += mi[k]; nx.j += mj[k];
            if (!isVal(nx) || mat[nx.i][nx.j] == '0')
                continue;
            nx.d = att.d + 1;
            nx.b = att.b + (mat[att.i][att.j] != mat[nx.i][nx.j]);

            pq.push(nx);
        }
    }

    if (fim.d == INT_MAX)
        printf("0 0\n");
    else
        printf("%d %d\n", fim.d, fim.b);
}
