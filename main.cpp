#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<unsigned int> numbers(unsigned int state) {
    std::vector<unsigned int> result;
    unsigned int mask = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;
    for (int i = 8; i >= 0; i--) {
        if ((state & mask) == mask) {
            result.push_back(i + 1);
        }
        mask /= 2;
    }
    return result;
}

unsigned int score(unsigned int state) {
    unsigned int s = 0;
    unsigned int decimal = 1;
    unsigned int mask = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;
    for (int i = 8; i >= 0; i--) {
        if ((state & mask) == mask) {
            s += (i + 1) * decimal;
            decimal *= 10;
        }
        mask /= 2;
    }
    return s;
}

int main() {
    std::unordered_map<unsigned int, float> states = {
        {0, 0},
        {1, 5.0f / 6.0f},
        {2, 2.0f * 5.0f / 6.0f},
        {3, 3.0f * 5.0f / 6.0f},
        {4, 4.0f * 5.0f / 6.0f},
        {5, 5.0f* 5.0f / 6.0f},
        {6, 6.0f * 5.0f / 6.0f},
    };

    std::unordered_map<unsigned int, float> probability{
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
        {12, 1.0f / 36.0f}
    };

    const unsigned int one = 1;
    const unsigned int two = 2;
    const unsigned int three = 2 * 2;
    const unsigned int four = 2 * 2 * 2;
    const unsigned int five = 2 * 2 * 2 * 2;
    const unsigned int six = 2 * 2 * 2 * 2 * 2;
    const unsigned int seven = 2 * 2 * 2 * 2 * 2 * 2;
    const unsigned int eight = 2 * 2 * 2 * 2 * 2 * 2 * 2;
    const unsigned int nine = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;

    for (unsigned int i: numbers(nine | one | two)) {
        std::cout << i << std::endl;
    }

    std::cout << score(nine | one | two) << std::endl;

    return 0;
}
