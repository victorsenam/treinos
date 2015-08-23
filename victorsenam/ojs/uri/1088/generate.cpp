#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

#define N 100000

unsigned long long int i, aux;
vector<unsigned long long int> v;

int main () {
    for (i = 0llu; i < N; i++) v.push_back(i);
        
    srand(time(0));
    random_shuffle(v.begin(), v.end());

    for (i = 0llu; i < N; i++) printf("%llu ", v[i]);
}
