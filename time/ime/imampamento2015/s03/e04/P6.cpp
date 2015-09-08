#include <bits/stdc++.h>

using namespace std;

const int pal[] = {6,2,5,5,4,5,6,3,7,6};
const int N = 107;

int dig[N], next[N];
int n;
int mini;

int main () {
    int t;
    scanf("%d", &t);
    
    dig[0] = 0;
    dig[1] = 10000;
    for (int i = 2; i < N; i++) {
        mini = 10;
        for (int j = 0; j < 10; j++) {
            if (i - pal[j] >= 0 && (mini == 10 || dig[i-pal[j]] < dig[i-pal[mini]])) 
                mini = j;
        }
        dig[i] = 1+dig[i-pal[mini]];
        next[i] = mini;
    }

    while (t--) {
        scanf("%d", &n);
        int aux = n;
        bool free = 0;
        
        mini = 10;
        for (int j = 1; j < 10; j++) {
            if (n - pal[j] >= 0 && (mini == 10 || dig[n-pal[j]] < dig[n-pal[mini]]))
                mini = j;
        }
        printf("%d", mini);
        n -= pal[mini];
        while (n > 0) {
            printf("%d", next[n]);
            n -= pal[next[n]];
        }
        printf(" ");

        n = aux;
        while (n) {
            if (n%2) {
                printf("7");
                n -= 3;
            } else {
                printf("1");
                n -= 2;
            }
        }

        printf("\n");
    }
}
