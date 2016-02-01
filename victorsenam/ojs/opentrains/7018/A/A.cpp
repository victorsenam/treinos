#include <bits/stdc++.h>

using namespace std;
const int N = 30;

bool mat[N][N][N];
int lim[3];

struct posi {
    int p[3];
    int d, s;

    bool operator == (const posi & ot) {
        for (int i = 0; i < 3; i++)
            if (p[i] != ot.p[i])
                return 0;
        return (d == ot.d && s == ot.s);
    }

    inline int occ (int ch) 
    { return (mat[p[0]][p[1]][p[2]] += ch); }

    inline void turn (int dir, int sen)
    { d = dir; s = sen; }

    void move (bool f) {
        occ(-(f));
        p[d] += !(s^f) - (s^f);
        occ(!f);
    }

    bool trymove() {
        move(0);
        bool flag = 1;
        for (int i = 0; i < 3 && flag; i++)
            flag &= (p[i] > 0 && p[i] <= lim[i]);
        if (flag) flag &= occ(0);
        if (!flag)
            move(1);
        return flag;
    }

    inline bool read() {
        char c;
        scanf("%d %d %d", p, p+1, p+2);
        scanf(" %c", &c);
        s = (c == '-');
        scanf(" %c", &c);
        d = (c - 'x');
    }

    inline void print() {
        printf("(%d,%d,%d) %c%c", p[0], p[1], p[2], s?'-':'+', d+'x');
    }
};

posi att, obj;

bool bt (int t) {
    if (att == obj) {
        printf("%d\n", t);
        return 1;
    }
    if (t >= 6)
        return 0;

    posi ini = att;

    if (!att.trymove()) return 0;
    if (!att.trymove()) { att.move(1); return 0; }

    for (int dir = 0; dir < 3; dir++) {
        if (dir == ini.d)
            continue;

        for (int sen = 0; sen < 2; sen++) {
            att.turn(dir, sen);
            int k = 2;
            while (k-- && att.trymove()); k++;
            if (!k) {
                printf("[%d]", t); ini.print(); printf(" -> "); att.print(); printf("\n");
                if (bt(t+1)) return 1;
            }
            while (k++ < 2) att.move(1);
            att.turn(ini.d,ini.s);

            if (!att.trymove()) continue;
            att.turn(dir, sen);
            if (att.trymove()) {
                printf("[%d]", t); ini.print(); printf(" -> "); att.print(); printf("\n");
                if (bt(t+1)) return 1;
                att.move(1);
            }
            att.turn(ini.d,ini.s);
            att.move(1);
        }
    }

    att.move(1);
    att.move(1);

    assert(ini == att);
    return 0;
}

int main () {
    int ts = 0;
    while (scanf("%d %d %d", lim, lim+1, lim+2) && lim[0]) {
        att.read(); obj.read();
        att.move(1);
        memset(mat, 0, sizeof mat);

        printf("Case %d: \n", ++ts);
        if (!bt(0))
            printf("Impossible\n");
    }
}
