#include <cstdio>

#define S 42195

int n, d, l, a, ok;

int main () {
    scanf("%d %d", &n, &d);
    scanf("%d", &l);
    n--;
    ok = 1;

    while (n--) {
        scanf("%d", &a);

        if (a-l > d) {
            printf("N\n");
            return 0;
        }

        l = a;
    }

    if (S-l > d) printf("N\n");
    else printf("S\n");
}
