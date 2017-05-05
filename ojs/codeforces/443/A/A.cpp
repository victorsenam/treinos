#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

char c;

int main () {
    scanf("%c", &c);


    set<char> s;
    while (scanf("%c", &c) != EOF) {
        if (isalpha(c))
            s.insert(c);
    }

    printf("%d\n", int(s.size()));
}
