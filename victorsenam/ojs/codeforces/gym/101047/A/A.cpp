#include <bits/stdc++.h>

using namespace std;
typedef unsigned int ui;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int R = 4;
const int N = 4;
const int K = N*R;
const int MASK = (1<<K);

int trump;
int r;

struct card {
    int suit;
    int val;

    bool beats (card ot) {
        if (suit == trump && ot.suit != trump) return 1;
        if (suit != ot.suit) return 0;
        return (val > ot.val);
    }

    int suitVal (char st) {
        if (st == 'H') return 0;
        if (st == 'S') return 1;
        if (st == 'C') return 2;
        if (st == 'D') return 3;
        return 4; // pra testar se rolou No Trump, muda isso pra 3
    }

    int cardVal (char cd) {
        if (cd == 'A') return 12;
        if (cd == 'K') return 11;
        if (cd == 'Q') return 10;
        if (cd == 'J') return 9;
        if (cd == 'T') return 8;
        return cd - '2';
    }

    void set (char a, char b) {
        suit = suitVal(a);
        val = cardVal(b);
    }
};

card v[N][R];
int visi[MASK][R][N][N], turn;
short memo[MASK][R][N][N];

struct state {
    int posi;
    int win;
    int suit;
    int mask;

    inline int getMask (int pl, int c)
    { return (1<<(pl*r+c)); }

    inline bool usedCard (int pl, int c)
    { return getMask(pl,c)&mask; }

    int hasSuit (int pl, int st) {
        for (int i = 0; i < r; i++)
            if (!usedCard(pl, i) && st == v[pl][i].suit)
                return 1;
        return 0;
    }

    bool useCard (int pl, int c) {
        if (usedCard(pl,c))
            return 0;
        card ch = v[pl][c];
        if (pl == win) {
            suit = ch.suit;
            posi = c;
            mask |= getMask(pl,c);
            return 1;
        } else {
            if (ch.suit != suit && hasSuit(pl, suit)) 
                return 0;
            card op = v[win][posi];
            if (ch.beats(op)) {
                win = pl;
                posi = c;
            }
            mask |= getMask(pl,c);
            return 1;
        }
    }

    int getTrick() {
        int mini = r;
        int att = mask;
        for (int i = 0; i < 4; i++) {
            mini = min(mini, (int) __builtin_popcount(att%(1<<r)));
            att /= (1<<r);
        }
        return mini;
    }

    int getPlayer(int tr) {
        int p[4];
        int att = mask;
        for (int i = 0; i < 4; i++) {
            p[i] = (int) __builtin_popcount(att%(1<<r));
            att /= (1<<r);
        }
        for (int i = 0; i < 4; i++)
            if (p[i] == tr && p[(i+3)%4] == tr+1) return i;
        return win;
    }

    bool visi () {
        if (::visi[mask][posi][win][suit] == turn) 
            return 1;
        ::visi[mask][posi][win][suit] = turn;
        return 0;
    }

    short & memo () {
        return ::memo[mask][posi][win][suit];
    }

    void opt (int pl, short val) {
        if (pl%2)
            memo() = min(memo(), val);
        else
            memo() = max(memo(), val);
    }
};

short pd (state s) {
    int tr = s.getTrick();
    if (tr == r) return !(s.win%2);
    
    int pl = s.getPlayer(tr);
    if (pl == s.win) s.posi = 0;

    if (s.visi()) return s.memo();

    if (pl%2) s.memo() = 4;
    else s.memo() = 0;

    state nx;

    for (int i = 0; i < r; i++) {
        nx = s;
        if (nx.useCard(pl, i))
            s.opt(pl, pd(nx));
    }

    if (pl == s.win)
        s.memo() += (!(s.win%2)&&tr);

    return s.memo();
}

int main () {
    char a, b, c;
    int ts;
    state s;
    s.posi = s.win = s.suit = s.mask = 0;
    scanf("%d", &ts);

    while (ts--) {
        turn++;
        scanf(" %c%c %d", &a, &b, &r);
        trump = v[0][0].suitVal(a);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < r; j++) {
                scanf(" %c%c", &a, &b);
                v[i][j].set(b, a);
            }
        }
        printf("%d\n", (int) pd(s));
    }
}
