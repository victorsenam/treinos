#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, current, i, occ;
    vector<int> numbers;
    vector<int>::iterator it;

    cin >> n;
    for( ; n > 0 ; n-- ){
        cin >> current;
        numbers.push_back(current);
    }

    sort(numbers.begin(), numbers.end());

    current = numbers.at(0);
    occ = 1;
    for( i = 1 ; i < numbers.size() ; i++){
        if( numbers.at(i) == current ) occ++;
        else{
            cout << current << " aparece " << occ << " vez(es)\n";
            current = numbers.at(i);
            occ = 1;
        }
    }
    cout << current << " aparece " << occ << " vez(es)\n";
}
