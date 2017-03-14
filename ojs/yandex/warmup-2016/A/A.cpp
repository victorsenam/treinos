#include <bits/stdc++.h>
using namespace std;

const int N = 1000007;
const char vwls[] = {'a', 'e', 'i', 'o', 'u', 'y'};

char str[N];
char res[2];

int main () {
    scanf(" %s", str);
    res[0] = res[1] = 0;

    for (int i = 0; str[i]; i++) {
        int k = 0;
        for (k = 0; k < 6 && vwls[k] != str[i]; k++);
        if (!res[(k==6)])
            res[(k==6)] = str[i];
    }

    if (res[0] > res[1]) printf("Vowel\n");
    else printf("Consonant\n");
}
