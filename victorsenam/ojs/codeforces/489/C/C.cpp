#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

int m, s;
stack<int> st;

int main () {
    scanf("%d %d", &m, &s);

    if (m == 1 && s == 0) {
        printf("0 0\n");
        return 0;
    }

    if (s == 0 || s > m*9) {
        printf("-1 -1\n");
        return 0;
    }

    int im = m;
    int is = s;

    s--;
    while (m > 0) {
        st.push(min(s,9));
        s -= min(s,9);
        m--;
    }
    printf("%d", st.top()+1);
    st.pop();
    while (!st.empty()) {
        printf("%d", st.top());
        st.pop();
    }
    printf(" ");

    m = im;
    s = is;

    while (m > 0) {
        printf("%d", min(s, 9));
        s -= min(s, 9);
        m--;
    }
    printf("\n");
}
