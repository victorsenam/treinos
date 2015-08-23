#include <bits/stdc++.h>

using namespace std;

string totwenty[20] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
    "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};
string dezens[8] = {
    "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
};


int main () {
    int n;
    scanf("%d", &n);
    if (n < 20) printf("%s\n", totwenty[n].c_str());
    else {
        printf("%s", dezens[n/10-2].c_str());
        if (n%10) {
            printf("-%s", totwenty[n%10].c_str());
        }
        printf("\n");
    }
}
