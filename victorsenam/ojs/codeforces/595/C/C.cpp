#include <bits/stdc++.h>

using namespace std;

int n;
int rem;
set<int> x;
set<int>::iterator it, jt;
map<int, vector<int> > s;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        x.insert(a);
    }

    it = x.begin();
    ++it;
    jt = x.begin();
    
    while (it != x.end()) {
        s[*jt-*it].push_back(*it);
    }

    bool ty = 1;
    while (x.size() > 2) {
        if (ty) {
            
        } else {
        }
        ty = !ty;
    }

    printf("%d\n", *(x.rbegin())-*(x.begin()));
}
