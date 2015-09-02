#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int S = 5007;

char str[S];
int suf[S];
int n;
int res;

bool sufComp (int a, int b) {
    return (strcmp(str+a, str+b) < 0);
}

int main () {
    scanf(" %s", str);
    int n = strlen(str);

    for (int i = 0; str[i] != '\0'; i++)
        suf[i] = i;
    
    res = n*(n+1)/2;

    sort(suf, suf+n, sufComp);

    for (int i = 0; i < n-1; i++) {
        int j = 0;

        while (*(str+suf[i]+j) == *(str+suf[i+1]+j))
            j++;


        res -= j;
    }

    printf("%d\n", res);
}
