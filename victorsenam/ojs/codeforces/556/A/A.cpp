#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 200007

int n;
char str[N];
int a, b, c;

int main () {
    scanf("%d", &n);
    scanf("%s", str);

    a = b = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '1') a++;
        else b++;
    }

    c = min(a, b);
    a -= c;
    b -= c;

    printf("%d\n", max(a,b));
}
