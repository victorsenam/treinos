#include <bits/stdc++.h>

int main() {
    char s[101];
    char cf[11] = "CODEFORCES";

    scanf(" %s", s);

    int i, j, k;
    k = strlen(s);
    for (i = 0; s[i] != '\n' && cf[i] == s[i]; i++);
    for (j = 0; k-j-1 >= 0 && cf[9-j] == s[k-j-1]; j++);

    if (i+j >= 10) printf("YES\n");
    else printf("NO\n");
}
