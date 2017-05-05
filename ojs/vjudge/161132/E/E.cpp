#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

int n;
char str[N];
int sm[N];
map<int, int> mp;

int get (int x) {
    if (x == 0) return 0;
    return x%10 + get(x/10);
}

int main () {
    for (int i = 0; i < N; i++) {
        int r =  get(i);
        sm[i] = mp[r-1];
        mp[r] = i;
    }


    while (scanf(" %s", str) != EOF) {
        if (str[0] == 'E') return 0;
        n = atoi(str);

        printf("%d\n", sm[n]);
    }

}
