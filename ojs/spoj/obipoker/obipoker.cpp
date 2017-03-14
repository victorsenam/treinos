#include <bits/stdc++.h>

using namespace std;

int cards[5], counts[13], t;
int max1, max2, fs, aux;

int main () {
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Teste %d\n", i);

        for (int j = 0; j < 13; j++) counts[j] = 0;

        fs = 13;
        for (int j = 0; j < 5; j++) {
            scanf("%d", &aux);
            aux--;
            if (aux < fs) fs = aux;
            counts[aux]++;
        }
        
        int k;
        for (k = fs; k < fs+5; k++) {
            if (counts[k] != 1) break;
        }
        if (k == fs+5) {
            printf("%d\n\n", fs+201);
            continue;
        }

        max1 = max2 = -1;
        for (int j = 0; j < 13; j++) {
            if (max1 == -1 || counts[j] >= counts[max1]) {
                max2 = max1;
                max1 = j;
            } else if (max2 == -1 || counts[j] >= counts[max2]) {
                max2 = j;
            }
        }

        if (counts[max1] == 4) {
            printf("%d\n\n", max1+181);
        } else if (counts[max1] == 3) {
            if (counts[max2] == 2) printf("%d\n\n", max1+161);
            else printf("%d\n\n", max1+141);
        } else if (counts[max1] == 2) {
            if (counts[max2] == 2) printf("%d\n\n", 3*max(max1, max2) + 2*min(max1, max2) + 25);
            else printf("%d\n\n", max1+1);
        } else {
            printf("0\n\n");
        }
    }
}
