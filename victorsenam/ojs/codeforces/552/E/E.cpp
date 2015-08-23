#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef ll num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 5003

char str[N];
int siz;
bool op;
num val;
num last;
num maxi;
num left;
num right;

int main () {
    scanf(" %s", str);
    val = 0;
    op = 0;
    last = str[0] - '0';
    for (siz = 1; str[siz] != '\0'; siz++) {
        if (str[siz] == '+') {
            val += last;
            last = (str[++siz] - '0');
        } else {
            last *= (str[++siz] - '0');
        }
    }
    val += last;
}
