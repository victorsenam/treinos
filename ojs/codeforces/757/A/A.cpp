#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 1e5+7;

const char let[8] = "Bulbasr";
int qt[7];
char str[N];

int main () {
    scanf(" %s", str);

    for (int i = 0; str[i]; i++) {
        for (int j = 0; j < 7; j++)
            if (str[i] == let[j])
                qt[j]++;
    }

    int mx = 1e5;
    for (int i = 0; i < 7; i++) {
        if (let[i] == 'u' || let[i] == 'a')
            mx = min(mx, qt[i]/2);
        else
            mx = min(mx, qt[i]);
    }

    printf("%d\n", mx);
}
