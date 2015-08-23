#include <algorithm>
#include <vector>
#include <cstdio>

#define MAX 10001

int inis[MAX], fims[MAX], ordfims[MAX], n, ini, fim, c;

bool orden (int a, int b) {
    return fims[a] < fims[b];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &inis[i], &fims[i]);
        ordfims[i] = i;
    }
//    printf("Read\n");

    std::sort(ordfims, ordfims+n, orden);
//    printf("Sorted\n");

    int j = 0, i = 0, c = 0;
    while (i < n) {
        if (ordfims[i] < j) i++;
        else {
            c++;
//            printf("%d(%d,%d) blocks from %d(%d,%d) to ", ordfims[i], inis[ordfims[i]], fims[ordfims[i]], j, inis[j], fims[j]);
            j = std::lower_bound(inis+j, inis+n, fims[ordfims[i]]) - inis;
//            printf("%d(%d,%d)\n", j, inis[j], fims[j]);
        }
    }
    
    printf("%d\n", c);
}
