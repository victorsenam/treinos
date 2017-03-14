#include <bits/stdc++.h>

using namespace std;

typedef struct {
    char n[18];
    int p, j, g, s;
} team;

map<string, int> mapa;
vector<team> teams;
team teama, teamb;
int t, j, auxa, auxb, inda, indb;
char tmpa[18], tmpb[18];

char tolow(char c) {
    if (c >= 'a' && c <= 'z') return c;
    if (c >= 'A' && c <= 'Z') return (c+'a'-'A');
    return c;
}

bool lt_str(char * a, char * b) {
    int i = 0;
    while (a[i] != '\0') {
        if (tolow(a[i]) < tolow(b[i])) return 1;
        if (tolow(a[i]) > tolow(b[i])) return 0;
        i++;
    }
    return (b[i] != '\0');
}

bool operator < (team a, team b) {
    if (a.p != b.p) return a.p > b.p;
    if (a.g - a.s != b.g - b.s) return a.g - a.s > b.g - b.s;
    if (a.g != b.g) return a.g > b.g;
    return lt_str(a.n, b.n);
}

void print_team (team a) {
    printf("%16s%4d%4d%4d%4d%4d",
        a.n,
        a.p,
        a.j,
        a.g,
        a.s,
        a.g-a.s
    );
    if (a.j == 0) printf("    N/A\n");
    else printf("%7.2f\n", (float) 100*a.p/(3*a.j));
}

int main () {
    while(scanf("%d %d", &t, &j) != EOF && t && j) {
        teama.p = teama.j = teama.g = teama.s = 0;
        teams.clear();
        mapa.clear();

        for (int i = 0; i < t; i++) {
            scanf(" %s", teama.n);            

            teams.push_back(teama);
            mapa.insert(make_pair(teama.n, i));
        }

        for (int i = 0; i < j; i++) {
            scanf(" %s %d - %d %s", tmpa, &auxa, &auxb, tmpb);

            inda = mapa.find(tmpa)->second;
            indb = mapa.find(tmpb)->second;

            teams[inda].j++;
            teams[indb].j++;

            teams[inda].g += auxa;
            teams[indb].g += auxb;

            teams[inda].s += auxb;
            teams[indb].s += auxa;

            teams[inda].p += (auxa>auxb)*3 + (auxa==auxb);
            teams[indb].p += (auxa<auxb)*3 + (auxa==auxb);
        }

        sort(teams.begin(), teams.end());
        
        printf(" 1.");
        print_team(teams[0]);
        for (int i = 1; i < t; i++) {
            if (teams[i].p != teams[i-1].p || teams[i].g - teams[i].s != teams[i-1].g - teams[i-1].s || teams[i].g != teams[i-1].g) {
                printf("%2d.", i+1);
            } else {
                printf("   ");
            }
            print_team(teams[i]);
        }
        printf("\n");
    }
}
