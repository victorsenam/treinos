#include <bits/stdc++.h>

using namespace std;

#define N 18

char str[N+2];

int main () {
    scanf(" %s", str);
    bool ok = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!i && str[i] == '9') printf("9");
        else if (str[i] - '0' >= 5) printf("%c", '9' - str[i] + '0');
        else printf("%c", str[i]);
    }
    printf("\n");
}
