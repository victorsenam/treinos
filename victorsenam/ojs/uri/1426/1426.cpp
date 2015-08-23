#include <bits/stdc++.h>

using namespace std;

int t, act = 0;
int lins[2][5];

inline int getBase(int top, int lef, int rig) {
    return (top-lef-rig)/2;
}

void printSides(int top, int lef, int rig) {
    printf("%d %d", (top-lef-rig)/2+lef, (top-lef-rig)/2+rig);
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &(lins[act][0]));
        printf("%d\n", lins[act][0]);

        for (int i = 2; i <= 5; i++) {
            for (int j = 0; j < i; j++) {
                scanf("%d", &(lins[1-act][j]));
            }
            
            for (int j = 0; j < i-1; j++) {
                printSides(lins[act][j], lins[1-act][j], lins[1-act][j+1]);
                if (j != i-2) printf(" ");
            }
            printf("\n");

            for (int j = 0; j < i-1; j++) {
                printf("%d %d ", lins[1-act][j], getBase(lins[act][j], lins[1-act][j], lins[1-act][j+1]));
            }
            printf("%d\n", lins[1-act][i-1]);

            act = 1-act;
        }
    }
}
