#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif
const int N = 1000000;
int t;
ll n;
bool visi[10];
int cnt;

void go (ll n) {
    while (n) {
        if (!visi[n%10]) cnt++;
        visi[n%10] = 1;
        n /= 10;
    }
}

int main () {
    scanf("%d", &t);
    int ts = 0;

    while (t--) {
        scanf("%lld", &n);
        for (int i = 0; i < 10; i++)
            visi[i] = 0;
        cnt = 0;
        ll curr = n;
        go(curr);

        for (ll i = 0; i <= N && cnt < 10; i++) {
            curr += n;
            go(curr);
        }

        printf("Case #%d: ", ++ts);
        if (cnt == 10)
            printf("%lld\n", curr);
        else
            printf("INSOMNIA\n");
    }

}
