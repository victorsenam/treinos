#include <bits/stdc++.h>

using namespace std;

#define N 16

typedef int num;

int n, m;
bool tab[N][N];
bool st[N][N];

void turn(int x, int y) {
    st[x][y] = !st[x][y];
    if (x-1 >= 0) st[x-1][y] = !st[x-1][y];
    if (x+1 < m) st[x+1][y] = !st[x+1][y];
    if (y-1 >= 0) st[x][y-1] = !st[x][y-1];
    if (y+1 < n) st[x][y+1] = !st[x][y+1];
}

int main () {
    while (scanf("%d %d", &m, &n) != EOF && m && n) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char a;
                scanf(" %c", &a);
                if (a == 'X') tab[i][j] = 1;
                else tab[i][j] = 0;
            }
        }

        num mini = INT_MAX;
        num count;
        for (int at = 0; at < 1<<n; at++) {
  //          printf("%d\n", at);
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    st[i][j] = tab[i][j];
            
            count = 0;
            for (int i = 0; i < n; i++) {
                if ((at>>i)%2) {
     //               printf("1");
                    turn(0, i);
                    count++;
                }
 //               else printf("0");
            }
   //         printf(" -> ");
     //       for (int i = 0; i < n; i++) printf("%d", st[0][i]);
       //     printf("\n");

            for (int i = 0; i < m-1; i++) {
                for (int j = 0; j < n; j++) {
                    if (st[i][j]) {
                        turn(i+1, j);
                        count++;
                    }
                }
            }

            int h;
            for (h = 0; h < n && !st[m-1][h]; h++);

            if (h >= n && mini > count) mini = count;
        }

        if (mini == INT_MAX) printf("Damaged billboard.\n");
        else printf("You have to tap %d tiles.\n", mini);
    }
}
