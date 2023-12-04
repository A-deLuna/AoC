#include <iostream>
#include <print>
#include <string>
#include <vector>

bool consider(std::vector<std::string> &v, int j, int i) {
  if (i > 0) {
    // already counted
    if (std::isdigit(v[j][i - 1]))
      return false;
    // left
    if (v[j][i - 1] != '.')
      return true;
  }
  // left up
  if (i > 0 && j > 0) {
    if (v[j - 1][i - 1] != '.' && !std::isdigit(v[j - 1][i - 1]))
      return true;
  }
  int m = v.size();

  // left down
  if (i > 0 && j < m - 1) {
    if (v[j + 1][i - 1] != '.' && !std::isdigit(v[j + 1][i - 1]))
      return true;
  }

  int n = v[0].size();
  for (; i < n && isdigit(v[j][i]); i++) {
    // up
    if (j > 0) {
      if (v[j - 1][i] != '.' && !std::isdigit(v[j - 1][i]))
        return true;
    }
    // down
    if (j < m - 1) {
      if (v[j + 1][i] != '.' && !std::isdigit(v[j + 1][i]))
        return true;
    }
  }

  // at one past the number
  if (i >= n)
    return false;
  if (j > 0) {
    if (v[j - 1][i] != '.' && !std::isdigit(v[j - 1][i]))
      return true;
  }
  // down
  if (j < m - 1) {
    if (v[j + 1][i] != '.' && !std::isdigit(v[j + 1][i]))
      return true;
  }
  // center
  if (v[j][i] != '.' && !std::isdigit(v[j][i]))
    return true;

  return false;
}
int main() {
  std::vector<std::string> v;
  std::string s;
  while (std::cin >> s) {
    v.emplace_back(std::move(s));
  }
  int total = 0;
  auto n = v[0].length();
  auto m = v.size();

  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      if (std::isdigit(v[j][i])) {
        if (consider(v, j, i)) {
          int num = 0;
          for (int a = i; a < n && std::isdigit(v[j][a]); a++) {
            num *= 10;
            num += v[j][a] - '0';
          }
          std::println("Found number: {0}", num);
          total += num;
        }
      }
    }
  }
  std::println("total: {0}", total);
}
