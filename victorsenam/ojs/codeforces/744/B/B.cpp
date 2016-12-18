#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;

const int N = 1e3+7;

int res[N];
int n;

void query (int b, int k) {
    vector<int> idx;
    
    for (int i = 1; i <= n; i++)
        if ( (k && (i&b)) || (!k && !(i&b)) )
            idx.push_back(i);

    if (idx.empty()) return;

    printf("%d\n", idx.size());
    for (int i : idx)
        printf("%d ", i);
    printf("\n");
    fflush(stdout);

    for (int i = 1; i <= n; i++) {
        int ret;
        scanf("%d", &ret);

        if ( (k && (i&b)) || (!k && !(i&b)) )
            continue;

        res[i] = min(res[i], ret);
    }
}

int main () {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        res[i] = INT_MAX;

    for (int i = 0; i < 10; i++) {
        query((1<<i), 0);
        query((1<<i), 1);
    }

    printf("-1\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
    fflush(stdout);
}
