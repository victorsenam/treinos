#include <bits/stdc++.h>

using namespace std;

int a, b;

int count (int val, int dig) {
    int res = 0, dest;
    int i = 1, c = 1;
    if (val < 10) return val >= dig;
    for (i = 1; val/i >= 10; i*= 10) {
        if ((val/i)%10 != 9) {
            res = i;
            dest = val - val%(i*10) - 1;
 //           printf("%d: %d - %d = %d\n", i, val, (val%(i*10)), dest);
            for (int j = i*10; val/j != 0; j*= 10) {
                if ((val/j)%10 == dig)
                    res += dest-val;
            }
            res += count(dest, dig);
            return res;
        } else {
            res += i*c;
        }
        c++;
    }
    return res + c*i*(dig==(val/i));
}

int main () {
    while (scanf("%d %d", &a, &b) != EOF && a && b) {
        for (int i = 0; i < 10; i++) {
            if (i) printf(" ");
            printf("%d", count(b,i)-count(a-1,i));
            printf("(%d,%d)", count(b,i), count(a-1,i));
        }
        printf("\n");        
    }
    while (scanf("%d", &a) != EOF && a) {

        for (int i = 0; i < 10; i++) {
            if (i) printf(" ");
            printf("%d", count(b,i)-count(a-1,i));
            printf("(%d,%d)", count(b,i), count(a-1,i));
        }
        printf("\n");        
    }
}
