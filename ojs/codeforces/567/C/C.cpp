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

const int N = 200014;

int n;
num k;
map<int, pair<num, num> > mp;
map<int, pair<num, num> >::iterator it;
num a[N];
num val1, val2, res;
int aux;

int main () {
    scanf("%d %d", &n, &aux);
    k = aux;

    for (int i = 0; i < n; i++) {
        scanf("%d", &aux);
        a[i] = aux;
    }
    
    res = 0;
    for (int i = n-1; i >= 0; i--) {
        if ((a[i]*k > 0 && a[i] < 0) || (a[i]*k < 0 && a[i] > 0))
            it = mp.end();
        else 
            it = mp.find(a[i]*k);

        if (it != mp.end()) {
            val1 = it->second.first;
            val2 = it->second.second;
        } else {
            val1 = 0;
            val2 = 0;
        }

        it = mp.find(a[i]);
        if (it == mp.end()) {
            mp.insert(make_pair(a[i], make_pair(1ll, val1)));
        } else {
            it->second.first++;
            it->second.second += val1;
        }

        res += val2;
        //printf("%d seq comecando de %d na pos %d\n", val2, a[i], i);
    }

    printf("%I64d\n", res);
}
