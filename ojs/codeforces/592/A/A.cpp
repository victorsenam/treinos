#include <bits/stdc++.h>

using namespace std;

int a, b;
char mat[10][10];

int main () {
    a = b = 8;

    scanf("%d %d", &a, &b);

    for (int i = 0; i < 8; i++)
        scanf(" %s", mat[i]);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (mat[j][i] == 'W')
                a = min(a, j);
            if (mat[j][i] != '.') {
                break;
            }
        }

        for (int j = 7; j >= 0; j--) {
            if (mat[j][i] == 'B')
                b = min(b, 7-j);
            if (mat[j][i] != '.')
                break;
        }
    }
    
    if (a <= b)
        printf("A\n");
    else
        printf("B\n");
}
