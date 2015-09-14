#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

set<int> know;
set<int>::iterator it;
int n;
int mark;

int main () {
    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {
        int j;
        for (j = 2; j < i; j++) {
            if (i%j == 0 && (i/j)%j != 0 && (i/j) > j)
                break;
        }
        know.insert(j);
    }

    printf("%d\n", know.size());
    for (it = know.begin(); it != know.end(); it++)
        printf("%d ", *it);
}
