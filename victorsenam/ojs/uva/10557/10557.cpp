#include <bits/stdc++.h>

using namespace std;

#define QTD 100

class edge {
public:
    int i;
    long long int e;
};

class vert {
public:
    int f, t;
};

bool operator < (edge a, edge b) {
    return a.e > b.e;
}

long long int ener[QTD];
int n, k, t;
bool seen[QTD];
edge salas[QTD];
vector<int> portas[QTD];
priority_queue<edge> fila;
vert vertaux;
edge edgeaux;

bool bfs (int i, int f) {
    if (i == f) return 1;

    seen[i] = 1;
    for (int j = 0; j < portas[i].size(); j++) {
        if (!seen[portas[i][j]] && bfs(portas[i][j], f)) return 1;
    }

    return 0;
}

int main () {
    while (scanf("%d", &n) != EOF && n != -1) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &(ener[i]));
            salas[i].e = 0;
            salas[i].i = i;
            seen[i] = 0;
            scanf("%d", &k);

            portas[i].clear();
            for (int j = 0; j < k; j++) {
                scanf("%d", &t);
                t--;
                portas[i].push_back(t);
            }
        }

        while(!fila.empty()) {
            edgeaux = fila.top();
            fila.pop();
//             printf("--> %d (%d) \n", edgeaux.i, edgeaux.e);
        };
/*
        printf("--------------- \n");
        for (int i = 0; i < n; i++) {
            printf("%d ", ener[i]);
        }
        printf("\n");
*/

        if (bfs(0,n-1)) {

            salas[0].e = 100;
            fila.push(salas[0]);

            while(!fila.empty()) {
                edgeaux = fila.top();
                fila.pop();
//                printf("--> %d (%d) \n", edgeaux.i, edgeaux.e);

                for (int j = 0; j < portas[edgeaux.i].size(); j++) {
                    int newen;

                    newen = salas[edgeaux.i].e + ener[portas[edgeaux.i][j]];
                    if (salas[portas[edgeaux.i][j]].e < newen) {
                        if (salas[portas[edgeaux.i][j]].e > 0) {
                            for (int i = 0; i < n; i++) seen[i] = 0;

                            if (bfs(portas[edgeaux.i][j], n-1)) {
                                salas[n-1].e = 1;
                                break;
                            }
                            else portas[portas[edgeaux.i][j]].clear();
                        }
                        salas[portas[edgeaux.i][j]].e = newen;
                        fila.push(salas[portas[edgeaux.i][j]]);
//                        printf("%d (%d) \n", salas[portas[edgeaux.i][j]].i, salas[portas[edgeaux.i][j]].e);
                    }
                }

                if (salas[n-1].e > 0) break;
            }

        }

/*
        for (int i = 0; i < n; i++) {
            printf("%d ", salas[i].e);
        }
        printf("\n");
*/

        if (salas[n-1].e == 0) printf("hopeless\n");
        else printf("winnable\n");
    }    
}
