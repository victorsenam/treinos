// INCOMPLETO
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int B = (1<<13);
const int N = 14;

int turn;
int memo[B];
int next[B];
int visi[N];
char card[N];
char suit[N];
int t;

int pd (int mask) {
    if (mask == B-1)
        return 0;
    int & me = memo[mask];

    if (visi[mask] == turn)
        return me;
    visi[mask] = turn;

    for (int i = 0; i < 13; i++) {
        if ((1<<i)&mask)
            continue;
        
        int chn = (1<<i);
        me = 1 + pd(mask|chn);
        next[mask] = chn;

        for (int j = i+1; j < 13; j++) { 
            if (((1<<j)&mask) || card[i] != card[j])
                continue;

            chn |= (1<<j);
            int loc = 1 + pd(mask|chn);
            if (me > loc) {
                me = loc;
                next[mask] = chn;
            }

            for (int k = j+1; k < 13; k++) {
                if (((1<<k)&mask) || card[i] != card[k])
                    continue;
                
                chn |= (1<<k);
                int loc = 1 + pd(mask|chn);
                if (me > loc) {
                    me = loc;
                    next[mask] = chn;
                }
                
                for (int l = k+1; l < 13; l++) {
                    if (((1<<l)&mask))
                        continue;

                    if (card[i] == card[l]) {
                        chn |= (1<<l);
                        int loc = 1 + pd(mask|chn);
                        if (me > loc) {
                            me = loc;
                            next[mask] = chn;
                        }
                    } else {
                        chn |= chn|(1<<l);
                        for (int g = l+1; g < 13; g++) {
                            if (((1<<g)&mask || card[l] != card[g])
                                continue;

                            chn |= (1<<g);
                            int loc = 1 + pd(mask|chn);
                            if (me > loc) {
                                me = loc;
                                next[mask] = chn;
                            }
                            chn &= ~(1<<g);
                        }
                    }

                    chn &= ~(1<<l);
                }
                chn &= ~(1<<k);
            }
            chn &= ~(1<<j);
        }

        for (int j = i+1; j < 13; j++) {
            if (((1<<j)|mask) || 
        }

        break;
    }

    return me;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < 13; i++)
            scanf(" %c%c", card+i, suit+i);
        
        turn++;
        printf("%d\n", pd(0));

        /*
        int att;
        while (att < B-1) {
            int to = next[att];
            for (int i = 1; i < B; i++) {
                if ((1<<i)&next[att])
                    printf("%c%c ", card[i], suit[i]);
            }
            att |= to;
        }  
        */
    }
}
