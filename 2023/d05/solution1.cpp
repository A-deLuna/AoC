#include <algorithm>
#include <iostream>
#include <print>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::string s;
  int total = 0;
  while (std::getline(std::cin, s)) {
    std::println("processing {0}", s);
    auto begin = std::ranges::find(s, ':');
    std::println("begin {0}", *begin);
    auto separator = std::ranges::find(begin, s.end(), '|');
    std::println("separator {0}", *separator);

    std::stringstream winningStream{std::string{begin+1, separator}};
    std::stringstream myNumbersStream{std::string{separator+1, s.end()}};

    std::set<int> winningNumbers;

    int n;
    while (winningStream >> n) {
      winningNumbers.insert(n);
      std::println("Winning numbers {0}", n);
    }

    int have = 0;
    while (myNumbersStream >> n) {
      std::println("my number {0}", n);
      if (winningNumbers.contains(n)) {
        have++;
      }
    }
    std::println("Found {0}", have);
    if (have == 0)
      continue;
    int i;
    for (i = 1; have > 1; have--, i *= 2)
      ;
    total += i;
    std::println("Adding {0}", i);
  }
  std::println("total {0}", total);
}
