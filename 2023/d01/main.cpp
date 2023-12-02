#include <cctype>
#include <iostream>
#include <print>
#include <string>
#include <string_view>
#include <vector>

std::array nums = {"one", "two",   "three", "four", "five",
                   "six", "seven", "eight", "nine"};

std::vector<int> numbers(const std::string &s) {
  std::vector<int> results;

  std::string_view sv{s};
  while (!sv.empty()) {
    for (auto i{1}; i < 10; i++) {
      if (sv.starts_with(nums[i - 1])) {
        results.push_back(i);
        continue;
      }
      if (std::isdigit(sv[0])) {
        results.push_back(sv[0] - '0');
      }
    }
    sv.remove_prefix(1);
  }
  return results;
}

int main() {
  auto total = 0;
  std::string s;
  while (std::cin >> s) {
    auto results = numbers(s);
    auto a = results.front();
    auto b = results.back();
    auto c = a * 10 + b;
    std::println("{1}, {2} = {3} : {0}", s, a, b, c);
    total += c;
  }
  std::println("{0}", total);
}
