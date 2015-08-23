#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 107

map<string, int> mp;
map<string, int>::iterator it;
int n;
char aux[N];


int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf(" %s", aux);
        it = mp.find(aux);
        if (it == mp.end()) mp.insert(make_pair(aux, 1));
        else it->second++;
    }

    int maxi = 0;
    for (it = mp.begin(); it != mp.end(); it++)
        maxi = max(maxi, it->second);

    printf("%d\n", maxi);
}
