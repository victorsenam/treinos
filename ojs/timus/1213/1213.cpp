#include<bits/stdc++.h>

using namespace std;

const int S = 32;

char temp[S], str[S];
set<string> s;

int main () {
    scanf(" %s", temp);

    while (scanf(" %[a-zA-Z0-9]-%[a-zA-Z0-9]", temp, str)) {
        s.insert(temp);
        s.insert(str);
    }

    if (s.size() == 0)
        printf("%d\n", 0);
    else
        printf("%d\n", s.size()-1);
}
