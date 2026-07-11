#include <iostream>

#ifdef RUN_NAIVE
// Run the naive coupled version (Member A responsibility)
void runNaiveDemo();
#else
// Run the refactored Observer pattern version (Member B responsibility)
void runPatternDemo();
#endif

int main() {
  std::cout << "=========================================\n";
#ifdef RUN_NAIVE
  std::cout << "    BANK ACCOUNT DEMO: NAIVE VERSION    \n";
#else
  std::cout << "    BANK ACCOUNT DEMO: PATTERN VERSION  \n";
#endif
  std::cout << "=========================================\n";

#ifdef RUN_NAIVE
  runNaiveDemo();
#else
  runPatternDemo();
#endif

  std::cout << "=========================================\n";
  return 0;
}
