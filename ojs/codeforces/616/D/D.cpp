#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1000006;

int n, k;
int resl, resr;
int l, r;
map<int, int> mp;
int cnt;
int a[N];

int main () {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", a+i);

    while (r < n) {
        mp[a[r]]++;
        if (mp[a[r]] == 1)
            cnt++;

        while (cnt > k) {
            mp[a[l]]--;
            if (mp[a[l]] == 0)
                cnt--;
            l++;
        }

        if (r - l > resr - resl) {
            resl = l;
            resr = r;
        }

        r++;
    }

    printf("%d %d\n", resl+1, resr+1);
}
