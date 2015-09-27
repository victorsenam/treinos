#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define MAX

int n;

int main () 
{
    string str;
    cin >> str;
    while (str.size() != 1)
    {
        string s;
        s.clear();
        int len = str.size();
        string sub1 = str.substr(0, len/2);
        string sub2 = str.substr(len/2, len);
        int s1 = stoi(sub1);
        int s2 = stoi(sub2);
        if (s1 < s2)
            s1++;
        string ss1 = to_string(s1);
        s.append(ss1);
        reverse(ss1.begin(), ss1.end());
        s.append(ss1);
        for (int i = 0; i < len-ss1.size(); i++) 
            s += "0";
        printf("%d\n", stoi(s)-stoi(str));
        cin >> str;
    }
}
