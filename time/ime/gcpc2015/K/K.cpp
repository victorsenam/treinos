#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100;
const char conv[10] = {'0', '1', '2', 'x', 'x', '5', '9', 'x', '8', '6'};
char str[N], aux[N];
ll a;

bool testprime () {
    if (a<=1)
        return 0;
    for (ll i = 2; i*i <= a; i++)
        if (a%i == 0)
            return 0;
    return 1;
}

int main () {
    scanf(" %s", str);
    a = atoll(str);

    if (!testprime()) {
        printf("no\n");
        return 0;
    }

    int l = strlen(str);
    for (int i = 0; i < l; i++) {
        aux[l-i-1] = conv[str[i]-'0'];
        if (aux[l-i-1] == 'x') {
            printf("no\n");
            return 0;
        }
    }
    aux[l] = 0;
    a = atoll(aux);
    if (testprime())
        printf("yes\n");
    else
        printf("no\n");
}
