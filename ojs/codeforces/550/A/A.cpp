#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 100002

char str[N];
vector<int> AB, BA;

int main () {
    scanf(" %s", str);
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] == 'B' && str[i-1] == 'A')
            AB.push_back(i);

        if (str[i] == 'A' && str[i-1] == 'B')
            BA.push_back(i);
    }

    if (AB.size() == 0 || BA.size() == 0) {
        printf("NO\n");
        return 0;
    }

    if (abs(AB[0] - BA[BA.size()-1]) != 1) {
        printf("YES\n");
        return 0;
    }

    if (abs(BA[0] - AB[AB.size()-1]) != 1) {
        printf("YES\n");
        return 0;
    }

    printf("NO\n");
}
