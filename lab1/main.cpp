#include <iostream>
#include "sol.h"

int main() {
    int lim;
    std::cout << "Enter limit: ";
    std::cin >> lim;
    
    std::pair<int, int> result = closest_pair_tonum(lim);
    std::cout << "closest_pair_tonum(" << lim << "): ("
              << result.first << ", " << result.second << ")" << std::endl;

    return 0;
}
