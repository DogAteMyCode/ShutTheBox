#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <vector>

std::vector<unsigned short> numbers(unsigned short state) {
    std::vector<unsigned short> result;
    unsigned short mask = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;
    for (int i = 8; i >= 0; i--) {
        if ((state & mask) == mask) {
            result.push_back(i + 1);
        }
        mask /= 2;
    }
    return result;
}

unsigned int n2state(std::vector<unsigned short> nums) {
    unsigned int result = 0;
    for (auto num: nums) {
        result |= num;
    }
    return result;
}

long factorial(const int n) {
    long f = 1;
    for (int i = 1; i <= n; ++i)
        f *= i;
    return f;
}

unsigned int score(unsigned short state) {
    unsigned int s = 0;
    unsigned int decimal = 1;
    unsigned short mask = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;
    for (int i = 8; i >= 0; i--) {
        if ((state & mask) == mask) {
            s += (i + 1) * decimal;
            decimal *= 10;
        }
        mask /= 2;
    }
    return s;
}

std::vector<std::vector<unsigned short> > combinations(const unsigned short n_arr[], unsigned short r,
                                                       unsigned short n = 9) {
    std::vector<std::vector<unsigned short> > result;
    if (r > n) { return result; }
    const long comb_n = factorial(n) / factorial(r) / factorial(n - r);
    result.reserve(comb_n);
    std::vector<unsigned short> combination;
    std::vector<unsigned short> indices(r);
    std::iota(indices.begin(), indices.end(), 0);

    for (unsigned short i: indices) {
        combination.push_back(n_arr[i]);
    }
    result.push_back(combination);
    combination.clear();

    while (true) {
        unsigned int i;
        bool ran = true;
        for (unsigned int j = r; j > 0; --j) {
            i = j - 1;
            if (indices[i] != i + n - r) {
                ran = false;
                break;
            }
        }
        if (ran) {
            return result;
        }
        indices[i] += 1;
        for (unsigned short j = i + 1; j < r; j++) {
            indices[j] = indices[j - 1] + 1;
        }
        for (unsigned short i: indices) {
            combination.push_back(n_arr[i]);
        }
        result.push_back(combination);
        combination.clear();
    }
}


int main() {
    const unsigned short one = 1;
    const unsigned short two = 2;
    const unsigned short three = 2 * 2;
    const unsigned short four = 2 * 2 * 2;
    const unsigned short five = 2 * 2 * 2 * 2;
    const unsigned short six = 2 * 2 * 2 * 2 * 2;
    const unsigned short seven = 2 * 2 * 2 * 2 * 2 * 2;
    const unsigned short eight = 2 * 2 * 2 * 2 * 2 * 2 * 2;
    const unsigned short nine = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;

    const unsigned short numbers_arr[] = {
        one, two, three, four, five, six, seven, eight, nine
    };

    std::unordered_map<unsigned short, float> states = {
        {0, 0},
        {one, 5.0f / 6.0f},
        {two, 2.0f * 5.0f / 6.0f},
        {three, 3.0f * 5.0f / 6.0f},
        {four, 4.0f * 5.0f / 6.0f},
        {five, 5.0f * 5.0f / 6.0f},
        {six, 6.0f * 5.0f / 6.0f},
    };

    std::unordered_map<unsigned short, unsigned short> number2number = {
        {0, 0},
        {one, 1},
        {two, 2},
        {three, 3},
        {four, 4},
        {five, 5},
        {six, 6},
        {seven, 7},
        {eight, 8},
        {nine, 9}
    };

    states.reserve(pow(2, 8) - 7);

    std::unordered_map<unsigned short, float> probability{
        {1, 0},
        {2, 1.0f / 36.0f},
        {3, 1.0f / 18.0f},
        {4, 1.0f / 12.0f},
        {5, 1.0 / 9.0f},
        {6, 5.0f / 36.0f},
        {7, 1.0f / 6.0f},
        {8, 5.0f / 36.0f},
        {9, 1.0f / 9.0f},
        {10, 1.0f / 12.0f},
        {11, 1.0f / 18.0f},
        {12, 1.0f / 36.0f},
        {13, 0},
        {14, 0},
        {15, 0},
        {16, 0},
        {17, 0},
    };

    for (unsigned short i = 6; i < sizeof(numbers_arr) / sizeof(unsigned short); i++) {
        states.insert({i + 1, probability[i + 1]});
    }

    std::vector<std::vector<unsigned short> > cmb = combinations(numbers_arr, 2);

    for (auto comb: cmb) {
        unsigned short state = n2state(comb);
        float hope = 0;

        for (auto num: comb) {
            unsigned short n_state = state ^ num;
            hope += states[n_state] * probability[number2number[num]];
        }

        float p_move = 0.0f;

        unsigned short total = 0;

        for (auto num: comb) {
            unsigned short n_state = state ^ num;
            p_move += probability[number2number[num]];
            total += number2number[num];
        }

        p_move += probability[total];

        unsigned int s = score(state);

        hope += s * (1-p_move);

        states[state] = hope;
    }

    for (auto state: states) {
        std::cout << score(state.first) << ": " << state.second << std::endl;
    }

    return 0;
}
