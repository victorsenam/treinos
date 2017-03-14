#include <bits/stdc++.h>

using namespace std;

const int N = 30;
const int M = 200007;

int freq[N];
int n;
int l, r;
char str[M];

int main() {
    scanf(" %s", str);
    
    for (n = 0; str[n]; n++)
        freq[str[n]-'a']++;
    
    int db = 0;
    for (int i = 0; i <= 'z'-'a'; i++)
        if (freq[i]%2)
            db++;

    int c = -1;
    l = 0;
    r = 'z'-'a';
    for (int i = 0; i < n/2; i++) {
        while (!freq[l]) l++;
        while (!(freq[r]%2)) r--;
        
        if (n%2 && db == 1 && freq[l] == 1) {
            c = l;
            l++;
            i--;
            continue;
        }

        if (freq[l] == 1) {
            freq[l]++;
            freq[r]--;
            db--;
            if (freq[r]%2)
                db++;
        }

        printf("%c", l+'a');
        str[i] = l+'a';
        freq[l] -= 2;
    }

    if (c == -1) {
        while (!freq[l]) l++;
        c = l;
    }

    if (n%2) {
        printf("%c", c+'a');
    }

    for (int i = (n/2)-1; i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}
