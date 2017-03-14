#include <bits/stdc++.h>

using namespace std;

typedef int num;

#define N 100000

char s[N];
char t[N];
char c;
int diff;

int main () {
    scanf(" %s", s);

    diff = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        scanf(" %c", &c);
        if (s[i] != c)
            diff++;

        if (diff%2) 
            t[i] = s[i];
        else
            t[i] = c;
    }

    if (diff%2) printf("impossible\n");
    else printf("%s\n", t);
}
