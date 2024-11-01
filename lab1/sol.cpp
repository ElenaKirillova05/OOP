#include "sol.h"
#include <cmath>

bool is_perfect_square(int x) {
    int root = static_cast<int>(std::sqrt(x));
    return root * root == x;
}

std::pair<int, int> closest_pair_tonum(int upper_limit) {
    std::pair<int, int> best_pair = {-1, -1};

    for (int m = upper_limit - 1; m > 0; --m) {
        for (int n = m - 1; n > 0; --n) {
            int sum_mn = m + n;
            int diff_mn = m - n;

            if (is_perfect_square(sum_mn) && is_perfect_square(diff_mn)) {
                std::pair<int, int> current_pair = {m, n};

                if (current_pair > best_pair) {
                    best_pair = current_pair;
                }
            }
        }
    }

    return best_pair;
}
