#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

pair<int, int> v[N];
int maxi;
int h;
int n;

void nope (){
    printf("-1\n");
    exit(0);
}

int main () {
    scanf("%d", &n);

    h = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &v[i].first, &v[i].second);
        if (v[i] > v[maxi])
            maxi = i;
    }

    for (int i = 0; i < n; i++) {
        if (i == maxi) continue;
        if (v[maxi].first <= v[i].first) nope();
        if (v[maxi].second <= v[i].second) nope();
    }

    printf("%d\n", maxi+1);


}
