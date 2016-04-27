#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

map<string, int> mp;
char str[N];
int n;

int main () {
    scanf("%d", &n);

    int maxi = 0;
    for (int i = 0; i < n; i++){
        scanf(" %s", str);
        sort(str, str+strlen(str));
        mp[str]++;
        maxi = max(maxi, mp[str]);
    }

    printf("%d\n", maxi);

}

