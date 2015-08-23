#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n,
        counter = 0,
        id = 0,
        current,
        overtakes = 0;
    vector<int>::iterator startIt;
    vector<int> startGrid;
    vector<int> endGrid;
    while(cin >> n)   {
        overtakes = 0;
        startGrid.clear();
        endGrid.clear();
        for( counter = 0 ; counter < n ; counter++ ){
            cin >> id;
            startGrid.push_back(id);
        }
        for( counter = 0 ; counter < n ; counter++) {
            cin >> id;
            endGrid.push_back(id);
        }
        for( counter = 0 ; counter < n ; counter++ ) {
            current = endGrid[counter];
            startIt = search_n(startGrid.begin(), endGrid.end(), 1, current);
            startGrid.erase(startIt);
            startGrid.insert((startGrid.begin() + counter),current);
            if((startIt - startGrid.begin()) > counter)
                overtakes += (startIt - startGrid.begin()) - counter;
        }
        cout << overtakes << endl;
    }
}
