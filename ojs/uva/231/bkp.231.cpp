#include <bits/stdc++.h>

/*
bool operator <(std::vector<std::pair<int,int> >::iterator a, std::vector<std::pair<int,int> >::iterator b) {
    return *a < *b;
}
*/

std::set<std::vector<std::pair<int,int> >::iterator> s;
std::vector<std::pair<int,int> >::iterator aux;
std::vector<std::pair<int,int> > v;
int n;
std::set<std::vector<std::pair<int,int> >::iterator>::iterator maxi, it;

int main() {
    assert(INT_MAX > 23767);
    
    while (scanf("%d", &n) != EOF && n != -1) {
        aux = v.end();
        v.push_back(std::make_pair(n, 1));
        s.insert(aux);


        while (scanf("%d", &n) != EOF && n != -1) {
            aux = v.end();
            v.push_back(std::make_pair(n, 1));
            it = s.lower_bound(aux);

            maxi = it;
            while (it != s.end()) {
                if ((*maxi)->second < (*it)->second) maxi = it;

                printf("(%d,%d) ", (*it)->first, (*it)->second);
                it++;
            }

            if (maxi == s.end()) v.back().second = 1;
            else v.back().second = (*maxi)->second + 1;

            printf(" --> (%d,%d)\n", v.back().first, v.back().second);
            s.insert(aux);
        }

        maxi = it = s.begin();
        while (it != s.end()) {
            if ((*maxi)->second < (*it)->second) maxi = it;

            printf("(%d,%d) ", (*it)->first, (*it)->second);
            it++;
        }

        printf(" === (%d,%d)\n", (*maxi)->first, (*maxi)->second);
        printf("%d\n", (*maxi)->second);

        s.clear();
    }
}
