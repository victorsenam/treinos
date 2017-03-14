#include <bits/stdc++.h>

using namespace std;

const int N = 10;

int n, v[N];
int t;
set<vector<int> > s;
vector<int> a;

bool troca(int i, int j) {
    swap(v[i], v[j]);
}

bool printa() {
    /*
    a.clear();
    for (int i = 0; i < n; i++)
        a.push_back(v[i]);
    if(s.find(a) != s.end()) printf("FAIL\n");
    s.insert(a);
    */
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]+1);
    printf("\n");
}


int solve (int n) {
    if (n == 2) {
        printa();
        troca(0, 1);
    } else {
        for (int i = 0; i < n; i++) {
            solve(n-1);
            if (i == n-1)
                continue;
            printa();
            for (int j = n-1; j > 0; j -= 2)
                troca(j-1, j);
        }
    }
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        v[i] = i;
    }

    solve(n);
    int f = 1;
    for (int i = 1; i <= n;i++)
        f *= i;

    printa();
 //   assert(s.size() == f);
}
