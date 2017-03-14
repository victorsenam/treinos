// BEGIN CUT HERE
// PROBLEM STATEMENT
// Correct parentheses sequences can be defined recursively as follows:

The empty string "" is a correct sequence.
If "X" and "Y" are correct sequences, then "XY" (the concatenation of X and Y) is a correct sequence.
If "X" is a correct sequence, then "(X)" is a correct sequence.
Each correct parentheses sequence can be derived using the above rules.

Examples of correct parentheses sequences include "", "()", "()()()", "(()())", and "(((())))".


We can define the depth of a correct parentheses sequence recursively as follows:


The empty string "" has depth 0.
If the depth of "X" is x and the depth of "Y" is y then the depth of "XY" is max(x,y).
If the depth of "X" is x then the depth of "(X)" is x+1.


For example, the depth of "(((())))" is 4, the depth of "()()()" is 1, and the depth of "(())()" is 2.

Note that the depth of each correct parentheses sequence is uniquely defined using the above rules.
For example, when evaluating the depth of "()()()" it does not matter whether we take X = "()" and Y = "()()" or we take X = "()()" and Y = "()", the result will be the same in both cases.


Given a string s that is a correct parentheses sequence, calculate and return the depth of s.

DEFINITION
Class:ParenthesesDiv2Easy
Method:getDepth
Parameters:string
Returns:int
Method signature:int getDepth(string s)


CONSTRAINTS
-s will contain between 2 and 50 characters, inclusive.
-Each character in s will be '(' or ')'.
-s will be a correct parentheses sequence.


EXAMPLES

0)
"(())"

Returns: 2


The depth of "" is 0.
Therefore, the depth of "()" is 1.
Next, the depth of "(())" is the depth of "()" plus 1, which makes it 1+1 = 2.


1)
"()()()"

Returns: 1


The depth of "()()" is the maximum of the depth of "()" and the depth of "()". In other words, it is max(1,1) = 1.
The depth of "()()()" is the maximum of the depth of "()()" and the depth of "()". Hence, this also equals max(1,1) = 1.


2)
"(())()"

Returns: 2

The answer is max(2, 1) = 2.

3)
"((())())(((())(()))())"

Returns: 4



4)
"()"

Returns: 1



// END CUT HERE
#line 89 "ParenthesesDiv2Easy.cpp"
#include <bits/stdc++.h>
using namespace std;
class ParenthesesDiv2Easy {
	public:
	int getDepth(string s) {
        int d = 0;
        int md = 0;
	    for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(')
                d++;
            if (s[i] == ')')
                d--;
            md = max(md, d);
        }
        return md;
	}
};
