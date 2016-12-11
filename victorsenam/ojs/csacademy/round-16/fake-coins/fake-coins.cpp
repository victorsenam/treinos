#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

int p[N];
int pv;
int res[2];
int n;

vector<int> v[3];
vector<int> v[3];
deque<int> curr;

void ans () {
    printf("A %d %d\n", res[0], res[1]);
    fflush(stdout);
    exit(0);
}

int query (vector<int> a, vector<int> b) {
    printf("%u %u", a.size(), b.size());
    for (int i : a)
        printf(" %d", i);
    for (int i : b)
        printf(" %d", i);
    printf("\n");
    fflush(stdout);

    int r;
    scanf("%d", &r);
    return r;
}

int main () {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        curr.push_back(i);

    if (n&1) {
        int r = query({1}, {n});
        if (r == 0) {
            curr.pop_back();
            v[2].push_back(n);
        } else {
            int t = !!(r + 1);
            r = query({1}, {2});
            if (r == 0) {
                res[!t] = curr[n];
                curr.pop_back();

                v[t] = curr;
                res[t] = getres(t);
                ans();
            } else if (r == -1) {
                res[t] = curr[1];
                curr.pop_front();

                v[!t] = curr;
                res[!t] = getres(!t);
                ans();
            } else {
                res[!t] = n;
                res[t] = 2;
                ans();
            }
        }
    }

    while (true) {
        curr.clear();
        for (int i = 0; i < v[0].size(); i++) {
            curr.push_back(v[0][i]);
            curr.push_back(v[1][i]);
        }

        v[0].clear();
        v[1].clear();
        for (int i = 0; i < curr.size()/2; i++)
            v[0].push_back(curr[i]);
        for (int i = curr.size()/2; i < curr.size(); i++)
            v[1].push_back(curr[i]);

        int r = query(v[0], v[1]);

        if (r == 1) {
            swap(v[0], v[1]);
        }

        if (r)
            break;
    }

    for (int t = 0; t < 2; t++) {
        vector<int> tmp[2];
        for (int i = 0; i < v[t].size() - (v[t].size()&1); i++)
            tmp[i&1].push_back(v[t][i]);

        int r = query(tmp[0], tmp[1]);
        
        if (r == 0) {
            res[r]
        }
    }
}
