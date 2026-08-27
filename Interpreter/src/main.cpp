#include <iostream>

void runNaiveDemo();
void runPatternDemo();

int main() {
    std::cout << "=========================================\n";
    std::cout << "      INTERPRETER PATTERN DEMONSTRATION \n";
    std::cout << "=========================================\n";

#ifdef RUN_NAIVE
    runNaiveDemo();
#elif defined(RUN_PATTERN)
    runPatternDemo();
#else
    runNaiveDemo();
    runPatternDemo();
#endif

    std::cout << "=========================================\n";
    return 0;
}
