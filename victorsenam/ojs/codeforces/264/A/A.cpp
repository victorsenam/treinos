#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

deque<int> q;
char str[N];
int n;

int main () {
    scanf(" %s", str);

    n = strlen(str);

    for (int i = n-1; i >= 0; i--) {
        if (str[i] == 'r')
            q.push_back(i+1);
        else
            q.push_front(i+1);
    }

    while (!q.empty()) {
        printf("%d\n", q.back());
        q.pop_back();
    }
}
