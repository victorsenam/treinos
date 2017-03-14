#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;
const char pat[] = "Value:";

char str[N];
char pref[N];
char out[N];
int ss, ps, os;
int lvl;
char c;
int mode;
int cols;
int cw[N];
int lins;
int cn;
int len[N];
vector<string> v;

map<string, string> mp;

void printsep () {
    putchar('+');
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < len[i]; j++) {
            putchar('-');
        }
        putchar('+');
    }
    putchar('\n');
}

int main () {
    scanf("%c", &c);
    lvl = 1;
    while (lvl) {
        scanf("%c", &c);
        if (mode == 0) { // buscando chave
            if (c == '"') {
                mode = 1;
            } else if (c == '}') {
                if (ps) ps--;
                while (ps && pref[ps-1] != '.') ps--;
                lvl--;
            }
        } else if (mode == 1) { // lendo chave
            if (c == '"') {
                mode = 2;
                pref[ps++] = '.';
            } else {
                pref[ps++] = c;
            }
        } else if (mode == 2) { // buscando valor
            if (c == '"') {
                mode = 3;
                lvl++;
            } else if (c == '{') {
                mode = 0;
                lvl++;
            }
        } else if (mode == 3) { // lendo valor
            if (c == '"') {
                mode = 0;
                str[ss++] = 0;
                pref[ps-1] = 0;
                mp[pref] = str;
                ss--; 
                ss = 0;
                if (ps) ps--;
                while (ps && pref[ps-1] != '.') ps--;
                lvl--;
            } else {
                str[ss++] = c;
            }
        }
    }


    while (scanf("%c", &c) && c != '\n');

    mode = 0;
    cols = -1;
    lins = 0;
    ss = 0;
    cn = 0;
    ps = 0;
    while (scanf("%c", &c) != EOF) {
        if (mode == 0) { // pegando largura das colunas
            if (c == '+')
                cols++;
            else if (c == '-')
                cw[cols]++;
            else if (c == '\n')
                mode = 1;
            len[cols] = 0;
        } else if (mode == 1) { // le o primeiro char da linha
            cn = 0;
            mode = 3;
            ss = 0;
            ps = 0;       
            os = 0;
        } else if (mode == 2) { // ignorando linha
            if (c == '\n') {
                mode = 1;
                lins++;
            }
        } else if (mode == 3) { // lendo linha
            if (c == '\n') {
                mode = 2;
            } else if (c == '|') {
                str[ss++] = 0;
                while (os && out[os-1] == ' ')
                    os--;
                out[os++] = 0;
                if (ps == 6 && mp.find(out) != mp.end()) {
                    v.push_back(mp[out]);
                    len[cn] = max(len[cn], (int)v[v.size()-1].length());
                } else {
                    v.push_back(str);
                    len[cn] = max(len[cn], cw[cn]);
                }

                cn++;
                ss = 0;
                ps = 0;
                os = 0;
            } else {
                str[ss++] = c;

                if (ps == 6) {
                    out[os++] = c;
                } else {
                    if (pat[ps] == c) ps++;
                    else ps = 0;
                }

            }
        }
    }
    for (int i = 0; i < lins; i++) {
        printsep();
        for (int j = 0; j < cols; j++) {
            putchar('|');
            printf("%s", v[i*cols+j].c_str());
            for (int k = v[i*cols+j].length(); k < len[j]; k++)
                putchar(' ');
        }
        putchar('|');
        putchar('\n');
    }
    printsep();
}
