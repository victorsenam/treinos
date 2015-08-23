#include <iostream>

using namespace std;

int main(){
    int first, second, sum;
    cin >> first >> second;
    if( first > second )
    {
        sum = second;
        second = first;
        first = sum;
    }

    for( sum = 0 ; first <= second ; first++ )
        if(first%13 != 0) sum += first;

    cout << sum << endl;
}
