#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int MD = 20;
int freq[MD], fst[MD];
int n, k, guess, fail, fre;
char in[MD];

int main()
{
    while( scanf(" %s", in) != EOF )
    {
        n = strlen(in);
        fill(freq, freq+10, 0);
        fill(fst, fst+10, k);
        fail = fre = 0;

        printf("[%s]\n", in);
        for(int i=0;i<n;i++)
        {
            if( !fre )
            {
            guess = in[i] - 48;
            while( guess >= 0 && freq[guess] >= 2 )
                guess--;
            if( guess == -1 )
            {
                fail = 1;
                break;
            }
            in[i] = guess + 48;
            freq[guess]++;
        }
        if(fail)
        {
            in[n-1] = 0;
            for(int i=0;i<n-1;i++)
                in[i] = 9 - i/2 + 48;
        }
        printf("%s\n", in);
    }
}
