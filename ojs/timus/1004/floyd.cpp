#include <bits/stdc++.h>

using namespace std;

const int N = 101;

int dist[N][N];
int from[N][N];
bool ini[N][N];
int n, m;
int a, b, d;

int main (){
    while (scanf("%d %d", &n, &m) != EOF && n >= 0) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                dist[i][j] = (i==j)?0:INT_MAX;
                from[i][j] = -1;
                ini[i][j] = 0;
            }
        
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &d);
            a--; b--;
            if (d < dist[a][b]) {
                dist[a][b] = d;
                from[a][b] = a;
                dist[b][a] = d;
                from[b][a] = b;
                ini[a][b] = ini[b][a] = 1;
            }
        }
        
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++) {
                    printf("%d ", dist[i][j]==INT_MAX?-1:dist[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int aux = max(max(dist[i][k], dist[k][j]), dist[i][k]+dist[k][j]);
                    if (aux < dist[i][j]) {
                        from[i][j] = from[k][j];
                        dist[i][j] = aux;
                        ini[i][j] = 0;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++)
            dist[i][i] = INT_MAX;

        for (int k = 0; k < m; k++) {
        }
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                printf("%d ", dist[i][j]==INT_MAX?-1:dist[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        int mini = 0;
        for (int i = 1; i < n; i++)
            if (dist[i][i] < dist[mini][mini])
                mini = i;

        printf("%d\n", dist[mini][mini]);
        if (dist[mini][mini] == INT_MAX)
            printf("No solution.\n");
        else {
            int aux = from[mini][mini];
            while (aux != mini){ 
                printf("%d ", aux+1);
                aux = from[mini][aux];
            }
            printf("%d\n", mini+1);
        }
    }
}
