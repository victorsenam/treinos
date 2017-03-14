#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;

char str[100];
char nm[N][7];
bool vl[N];
int n;

map<string, int> mp;

string mount (int i) {
    char aux[6];
    aux[0] = nm[i][0];
    aux[1] = nm[i][1];
    aux[2] = nm[i][2+vl[i]];
    aux[3] = 0;
    return string(aux);
}

void put (string curr, int i) {
    if (mp.find(curr) == mp.end()) {
        mp[curr] = i;   
    } else {
        int j = mp[curr];
        mp.erase(curr);

        if (vl[i] == 1 && vl[j] == 1) {
            printf("NO\n");
            exit(0);
        }

        vl[i] = 1;
        vl[j] = 1;

        put(mount(i), i);
        put(mount(j), j);
    }
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %s", str);
        nm[i][0] = str[0];
        nm[i][1] = str[1];
        nm[i][2] = str[2];

        scanf(" %s", str);
        nm[i][3] = str[0];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int k = 0;   
            while (k < 3 && nm[i][k] == nm[j][k])
                k++;
            if (k == 3)
                vl[i] = vl[j] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        put(mount(i), i);
    }

    printf("YES\n");
    for (int i = 0; i < n; i++)
        printf("%s\n", mount(i).c_str());
}
