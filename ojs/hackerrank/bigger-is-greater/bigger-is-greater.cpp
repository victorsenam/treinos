#include <bits/stdc++.h>

using namespace std;

const int N = 107;
int t, n, i;
char str[N];

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf(" %s", str);
        n = strlen(str);
        for (i = n-2; i >= 0 && str[i] >= str[i+1]; i--);
        if (i < 0)
            printf("no answer\n"); 
        else {
            sort(str+i+1, str+n);
            int j = upper_bound(str+i+1, str+n, str[i]) - str;
            swap(str[j], str[i]);
            for (j = 1; j+i < n; j++)
                swap(str[i+j], str[n-j]);
            printf("%s\n", str);
       }
    }
}
