#include <cstdio>
#include <cstring>

using namespace std;

int Dx[] = {-1, 0, 1, 0};
int Dy[] = {0, 1, 0, -1};

int main () {
    int N, M, S, posi, posj, i, j, dir, figs;
    char grid[102][103], temp, comm[50004];
    char ref[4] = {'N', 'L', 'S', 'O'};

    while (scanf("%d %d %d", &N, &M, &S) != EOF && N!=0 && M!=0 && S!=0) {
        figs = 0;
        for (i=0; i < N; i++) {
            scanf("%s ", grid[i]);
            for (j=0; j < M; j++) {
                temp = grid[i][j];
                if ( temp == 'N' || temp == 'O' || temp == 'L' || temp == 'S' ) {
                    posi = i;
                    posj = j;
                }
            }
        }

        for (i = 0; i < 4; i++) {
            if (grid[posi][posj] == ref[i]) {
                dir = i;
                i = 4;
            }
        }

        scanf("%s ", comm);

        for (i=0; i < S; i++) {
            if ( comm[i] == 'E' ) dir = (dir+3)%4;
            else if ( comm[i] == 'D' ) dir = (dir+1)%4;
            else if (posi + Dx[dir] != N && posj + Dy[dir] != M && posi + Dx[dir] >= 0 && posj + Dy[dir] >= 0) {
                temp = grid[posi + Dx[dir]][posj + Dy[dir]];

                if ( temp != '#' ) {
                    grid[posi][posj] = '.';
                    if( temp == '*' ) figs++;
                    posi += Dx[dir];
                    posj += Dy[dir];
                }
            }
        }

        printf("%d\n", figs);
    }
}
