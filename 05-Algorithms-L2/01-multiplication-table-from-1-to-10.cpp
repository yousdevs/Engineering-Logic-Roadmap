#include <iostream>

int main() {
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            std::cout << i << " x " << j << " = " << (i * j);
            if (j < 10) std::cout << '\t';
        }
        std::cout << '\n';
    }
    return 0;
}
