#include <bits/stdc++.h>

using namespace std;

#define C 51

int c, e, l, p, aa, ab, t, ok;
vector<int> graph[C];
bool visited[C];

void visit(int f, int p) {
    if (p < 0 || visited[f]) return;

    visited[f] = 1;
    for (int i = 0; i < graph[f].size(); i++) {
        visit(graph[f][i], p-1);
    }
}

int main () {
    t = 0;
    while (scanf("%d %d %d %d", &c, &e, &l, &p) != EOF && c && e && l && p) {
        ok = 0;
        l--;
        for (int i = 0; i < c; i++) {
            graph[i].clear();
            visited[i] = 0;
        }
        for (int i = 0; i < e; i++) {
            scanf("%d %d", &aa, &ab);
            graph[aa-1].push_back(ab-1);
            graph[ab-1].push_back(aa-1);
        }

        visit(l, p);

        printf("Teste %d\n", ++t);
        for (int i = 0; i < c; i++) {
            if (i != l && visited[i]) {
                if (ok) printf(" ");
                else ok = 1;
                printf("%d", i+1);
            }
        }
        printf("\n\n");
    }
}

