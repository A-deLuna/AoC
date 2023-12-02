#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>

int main() {
  std::string s;
  int game = 1;
  int total = 0;
  for (; std::getline(std::cin, s); ++game) {
    // Skip past 'Game n: '
    auto begin = std::ranges::find(s, ':') + 1;
    bool possible = true;
    for (; begin != s.end();) {
      if (*begin == ';')
        begin++;
      auto end = std::ranges::find(begin, s.end(), ';');
      std::stringstream ss(std::string(begin, end));
      int cnt;
      std::string color;
      while (ss >> cnt >> color) {
        std::println("parsed: {0} {1}", cnt, color);
        if (color.starts_with("red") && cnt > 12) {
          possible = false;
        }
        if (color.starts_with("green") && cnt > 13) {
          possible = false;
        }
        if (color.starts_with("blue") && cnt > 14) {
          possible = false;
        }
      }
      begin = end;
    }
    std::println("Game {0}: possible? {1}", game, possible);
    if (possible) {
      total += game;
    }
  }
  std::println("Total: {0}", total);
}
