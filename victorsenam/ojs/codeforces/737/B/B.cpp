#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5+7;
int n, a, b, k;

char str[N];
queue<pair<int, int> > qu;
vector<int> res;

int add (int s, int st) {
    qu.push(pair<int,int>(s, st));
    return s/b;
}

int main () {
    scanf("%d %d %d %d", &n, &a, &b, &k);

    scanf(" %s", str);

    int ls = 0;
    int qt = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == '1') {
            qt += add(i-ls, ls);
            ls = i+1;
        }
    }
    qt += add(n-ls, ls);

    while (qt >= a) {
        pair<int, int> att = qu.front();
        qu.pop();
        
        if (att.first >= b) {
            qt--;
            att.first -= b;
            att.second += b;
            qu.push(att);
            res.push_back(att.second);
        }
    }

    printf("%d\n", int(res.size()));
    for (int i = 0; i < res.size(); i++)
        printf("%d ", res[i]);
}
