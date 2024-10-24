#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <fstream>

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

unsigned short numbers2state(std::vector<unsigned short> nums) {
    unsigned int result = 0;
    for (auto num : nums) {
        result |= static_cast<unsigned short>(std::pow(2, num-1));
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

unsigned short addition(std::vector<unsigned short> nums) {
    unsigned short result = 0;
    for (auto num : nums) {
        result += num;
    }
    return result;
}

std::vector<std::vector<unsigned short>> combinations(const unsigned short n_arr[], unsigned short r,
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

unsigned short best_state_sum(unsigned short state, unsigned short sum, std::unordered_map<unsigned short, float> states) {
    const std::vector<unsigned short> numerals = numbers(state);

    const unsigned short n = numerals.size();

    unsigned short total = addition(numerals);

    unsigned short result = 0;
    float hope = 12345678910.0f;

    for (unsigned short i = 1; i < n; ++i) {
        for (auto comb: combinations(numerals.data(), i, n)) {
            unsigned short s = addition(comb);
            if (total - s == sum) {
                unsigned short new_state = numbers2state(comb);
                float new_hope = states[new_state];
                if (hope > new_hope) {
                    result = new_state;
                    hope = new_hope;
                }
            }
        }
    }

    return result;

}

template <typename t> bool in(t val, std::vector<t> vec) {
    for (auto v: vec) {
        if (v == val) {
            return true;
        }
    }
    return false;
}

std::vector<unsigned short> available(unsigned int state) {
    const std::vector<unsigned short> numerals = numbers(state);

    std::vector<unsigned short> result;

    for (unsigned short i = 1; i <= 12; i++) {
        if (in(i, numerals)) {
            result.push_back(i);
            continue;
        }
        bool found = false;
        for (int j = 1; j <= 4; j++) {
            for (auto comb: combinations(numerals.data(), j, numerals.size())) {
                unsigned short s = addition(comb);
                if (s == i) {
                    result.push_back(i);
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
    }

    return result;

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

    for (unsigned short i = 7; i <= 9; i++) {
        unsigned short p = numbers_arr[i-1];
        states[p] = static_cast<float>(i)*(1.0f - probability[i]);
    }

    std::vector<std::vector<unsigned short> > cmb = combinations(numbers_arr, 2);

    // Code for combinations of length 2,3,4,5,6,7,8,9
    for (unsigned short r = 2; r <= 9; r++)
    {
        cmb = combinations(numbers_arr, r);
        for (auto comb: cmb) {
            const unsigned short state = n2state(comb);
            float hope = 0;

            const std::vector<unsigned short> av = available(state);

            for (unsigned short i = 2; i <= 12; i++) {
                if (in(i, av)) {
                    unsigned short best_s = best_state_sum(state, i, states);
                    hope += states[best_s] * probability[i];
                }
                else {
                    hope += static_cast<float>(score(state)) * probability[i];
                }
            }

            states[state] = hope;
        }
    }

    std::ofstream MyFile;

    MyFile.open("C:/Users/ethan/CLionProjects/ShutTheBox/output.json");

    MyFile << "{" << std::endl;
    unsigned short s = states.size();
    unsigned short total = 0;
    for (auto state: states) {
        MyFile << '"' << score(state.first) << '"' << ": " << std::fixed << state.second;
        total += 1;
        if (total != s) {
            MyFile << "," << std::endl;
        } else {
            MyFile << std::endl;
        }
    }

    MyFile << "}";

    MyFile.close();

    unsigned short current_state = one | two | three | four | five | six | seven | eight | nine;

    std::vector<unsigned short> av = available(current_state);

    while (score(current_state) != 0) {
        std::string inp;
        std::cout << score(current_state) << std::endl;
        std::cout << "Enter dice roll: ";
        std::cin >> inp;
        unsigned short dice = std::stoi(inp);

        av = available(current_state);

        if (! in(dice, av)) {
            break;
        }

        current_state = best_state_sum(current_state, dice, states);
    }

    std::cout << "Final score is: " << score(current_state) << std::endl;

    return 0;
}
