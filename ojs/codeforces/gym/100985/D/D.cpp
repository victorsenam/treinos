#include<bits/stdc++.h>

using namespace std;

const int mov[6][8][2] = 
{
    { {1, -1}, {1, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
    { {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1} },
    { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
    { {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
    { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} },
    { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} }
};

const int qtd[6] = {2, 8, 4, 4, 8, 8};
const bool inf[6] = {0, 0, 1, 1, 1, 0};
const char let[6] = {'p', 'c', 't', 'b', 'r', 'k'};

char mat[10][10];
char c;
int p[2];
int a[2];

inline bool isVal (int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
        return 0;
    return 1;
}

inline bool isDead (int x, int y, int t) {
    if (!isVal(x, y)) return 0;
    return (mat[x][y] == let[t]);
}

inline bool isEmpty (int x, int y) {
    if (!isVal(x, y)) return 0;
    return (mat[x][y] == '.');
}

int main () {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            scanf(" %c", &mat[i][j]);
    scanf(" %c", &c);
    p[1] = c-'a';
    scanf("%d", p+0);
    p[0]--;
    p[0] = 7 - p[0];

    for (int i = 0; i < 6; i++) {
        for (int k = 0; k < qtd[i]; k++) {
            a[0] = p[0]; a[1] = p[1];

            do {
                a[0] += mov[i][k][0];
                a[1] += mov[i][k][1];
                if (isDead(a[0], a[1], i)) {
                    printf("Sim\n");
                    return 0;                    
                }
            } while (inf[i] && isEmpty(a[0], a[1]));
        }
    }
    printf("Nao\n");
}
