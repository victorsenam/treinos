#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 100;

char str[3][N];

int main () {
    scanf(" %s %s", str[0], str[1]);
    printf("%s %s\n", str[0], str[1]);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %s", str[2]);

        bool c = (strcmp(str[2], str[1]) == 0);

        scanf(" %s", str[c]);
        printf("%s %s\n", str[0], str[1]);
    }
}
