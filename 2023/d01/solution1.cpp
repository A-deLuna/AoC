#include <algorithm>
#include <cctype>
#include <iostream>
#include <print>
#include <ranges>

int main() {
  std::string s;
  auto total = 0;
  while (std::cin >> s) {
    auto is_char = [](auto c) { return std::isdigit(c); };
    auto first = std::ranges::find_if(s, is_char);
    auto last = std::ranges::find_if(std::views::reverse(s), is_char);

    auto a = *first - '0';
    auto b = *last - '0';
    auto c = a * 10 + b;
    std::println("{0} {1} {2}", a, b, c);
    total += c;
  }
  std::println("{0}", total);
}
