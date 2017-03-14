#include <bits/stdc++.h>

using namespace std;

const int N = 400;

char str[N];
int res;

int main () {
    scanf(" %s", str);
    res = 0;
    for (int i = 0; str[i]; i++) {
        if (i%3 == 0)
            res += (str[i] != 'P');
        else if (i%3 == 1)
            res += (str[i] != 'E');
        else
            res += (str[i] != 'R');
    }
    printf("%d\n", res);
}
