// BEGIN CUT HERE
// PROBLEM STATEMENT
// Correct parentheses sequences can be defined recursively as follows:

The empty string "" is a correct sequence.
If "X" and "Y" are correct sequences, then "XY" (the concatenation of X and Y) is a correct sequence.
If "X" is a correct sequence, then "(X)" is a correct sequence.
Each correct parentheses sequence can be derived using the above rules.

Examples of correct parentheses sequences include "", "()", "()()()", "(()())", and "(((())))".


You have a string s of length n, where n is even.
Your task is to change it into a correct parentheses sequence.
In order to do that, you are allowed to flip some parentheses.
Flipping a parenthesis changes it from '(' to ')' and vice versa.



There is always a way to change s into a correct parentheses sequence by doing at most (n/2)+1 flips.
Find any such sequence of flips.
Return a vector <int> containing a sequence of 0-based indices of parentheses in s you want to flip.

DEFINITION
Class:ParenthesesDiv2Medium
Method:correct
Parameters:string
Returns:vector <int>
Method signature:vector <int> correct(string s)


CONSTRAINTS
-s will contain between 2 and 50 characters, inclusive.
-The length of s will be even.
-Each character in s will be '(' or ')'.


EXAMPLES

0)
")("

Returns: {0, 1 }

The returned sequence represents the following sequence of changes:

Start with the string ")(".
Flip character 0. This produces the string "((".
Flip character 1. This produces the string "()", which is a corrent parentheses sequence.


1)
")))))((((("

Returns: {0, 2, 4, 5, 7, 9 }

Performing the flips described by the returned sequence changes the given string into the corrent parentheses sequence "()()()()()".
The answer {2, 0, 4, 9, 7, 5} would also be valid, as the order in which we perform the flips does not matter.
However, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} is not a valid answer: this sequence of flips does produce a correct parentheses sequence but the number of flips is too large.
As the length of s is 10, we may only perform at most 10/2 + 1 = 6 flips.

2)
"((()"

Returns: {1 }



3)
")))(()(())))))"

Returns: {0, 1, 2 }

Here, {0, 1, 2, 3, 3} would also be a valid answer.
Flipping the same parenthesis twice is allowed, even though it is clearly useless.

4)
"()()()()()()()()()()()()()"

Returns: { }



// END CUT HERE
#line 86 "ParenthesesDiv2Medium.cpp"
#include <bits/stdc++.h>
using namespace std;
class ParenthesesDiv2Medium {
	public:
	vector <int> correct(string s) {
	    vector <int> res;	
        int cnt = 0;
        int d = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                if (cnt + cnt >= s.length()) {
                    res.push_back(i);
                    s[i] = ')';
                }
            } else if (s[i] == ')') {
                if (d == 0) {
                    res.push_back(i);
                    s[i] = '(';
                }
            }

            if (s[i] == '(') {
                d++;
                cnt++;
            } else if (s[i] == ')')
                d--;
        }
        return res;
	}
};
