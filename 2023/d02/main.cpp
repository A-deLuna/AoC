#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <print>
#include <sstream>
#include <string>

int main() {
  int game = 1;
  int total = 0;
  std::string s;
  for (; std::getline(std::cin, s); ++game) {
    // Skip past 'Game n:'
    auto begin = std::ranges::find(s, ':');

    std::array rgb = {"red", "green", "blue"};
    std::array max = {0, 0, 0};

    for (std::string::iterator end; begin != s.end(); begin = end) {
      // begin might be pointing to a previous ';', skip it
      if (begin != s.end())
        ++begin;

      // end is either ';' or s.end()
      end = std::find(begin, s.end(), ';');

      // copy string segment into a stringstream to simplify parsing.
      std::stringstream ss{std::string{begin, end}};

      int count;
      std::string color;
      while (ss >> count >> color) {
        for (auto i{0}; i < rgb.size(); ++i) {
          if (color.starts_with(rgb[i])) {
            max[i] = std::max(max[i], count);
          }
        }
      }
    }
    auto power = std::accumulate(max.begin(), max.end(), 1, std::multiplies{});
    std::println("Game {0}: power {1}", game, power);
    total += power;
  }
  std::println("Total: {0}", total);
}
