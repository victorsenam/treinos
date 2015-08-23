#include <bits/stdc++.h>

using namespace std;

typedef int num;

#define N 100

bool good[N];
int n;
int a;
int goods;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) good[i] = 1;
    goods = n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a);
            if (a == -1 || a == 0) continue;
            if ((a == 3 || a == 1) && good[i]) {
                good[i] = 0;
                goods--;
            }
            if ((a == 3 || a == 2) && good[j]) {
                goods--;
                good[j] = 0;
            }
        }
    }
    
    printf("%d\n", goods);
    for (int i = 0; i < n; i++) {
        if (good[i]) printf("%d ", i+1);
    }

    printf("\n");
        
}
