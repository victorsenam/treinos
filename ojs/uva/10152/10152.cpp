#include <bits/stdc++.h>

using namespace std;

const int N = 207;
const int S = 87;

int n, t;
char nm[N][S];
char ob[N][S];

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        
        for (int i = 0; i < n; i++)
            scanf("\n%[0-9a-zA-Z .]s", nm+i);
        for (int i = 0; i < n; i++)
            scanf("\n%[0-9a-zA-Z .]s", ob+i);

        int j = n-1;
        for (int i = n-1; i >= 0; i--) {
            if (strcmp(nm[i], ob[j]) == 0)
                j--;
        }

        for (; j >= 0; j--)
            printf("%s\n", ob[j]);
        printf("\n");
    }
}
