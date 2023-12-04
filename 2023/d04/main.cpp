#include <algorithm>
#include <iostream>
#include <print>
#include <unordered_set>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::string s;
  int total = 0;
  std::vector<int> games(200, 1);
  for (int game = 1; std::getline(std::cin, s); game++) {
    std::println("processing {0}", s);
    auto begin = std::ranges::find(s, ':');
    auto separator = std::ranges::find(begin, s.end(), '|');

    std::stringstream winningStream{std::string{begin + 1, separator}};
    std::stringstream myNumbersStream{std::string{separator + 1, s.end()}};

    std::unordered_set<int> winningNumbers;

    int n;
    while (winningStream >> n) {
      winningNumbers.insert(n);
    }

    int have = 0;
    while (myNumbersStream >> n) {
      if (winningNumbers.contains(n)) {
        have++;
      }
    }
    std::println("Found {0}", have);

    std::println("Scratching {0} cards of game {1}", games[game], game);
    total += games[game];
    for (int i = game + 1; i < game + 1 + have; i++) {
      games[i] += games[game];
    }
  }
  std::println("total {0}", total);
}
