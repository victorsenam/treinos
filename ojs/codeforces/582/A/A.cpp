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

const int N = 507;

int n;
int a;
multiset<int> s;
multiset<int>::iterator it;
int res[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n*n; i++) {
        scanf("%d", &a);
        s.insert(a);
    }

    for (int i = 0; i < n; i++) {
        it = s.end();
        --it;

        res[i] = *it;
        s.erase(it);

        for (int j = 0; j < i; j++) {
            s.erase(s.find(__gcd(res[i], res[j])));
            s.erase(s.find(__gcd(res[i], res[j])));
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d ", res[i]);
    printf("\n");
}
