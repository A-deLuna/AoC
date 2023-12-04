#include <iostream>
#include <print>
#include <string>
#include <vector>

int parseRight(std::vector<std::string> &v, int j, int i) {
  int n = v[0].size();
  int num = 0;
  for (; i < n && std::isdigit(v[j][i]); i++) {
    num *= 10;
    num += v[j][i] - '0';
    // std::println("ParseRight num = {0}", num);
  }
  return num;
}

int parseLeft(std::vector<std::string> &v, int j, int i) {
  int num = 0;
  for (int pow = 1; i >= 0 && std::isdigit(v[j][i]); i--, pow *= 10) {
    num += pow * (v[j][i] - '0');
    // std::println("ParseLeft num = {0}", num);
  }
  return num;
}

std::vector<int> consider(std::vector<std::string> &v, int j, int i) {
  std::println("searching");
  std::vector<int> nums;
  // left
  if (i > 0 && std::isdigit(v[j][i - 1])) {
    int num = parseLeft(v, j, i - 1);
    nums.push_back(num);
    std::println("Left");
  }
  // right
  int n = v[0].size();
  if (i < n - 1 && std::isdigit(v[j][i + 1])) {
    int num = parseRight(v, j, i + 1);
    nums.push_back(num);
    std::println("Right");
  }

  // top
  if (j > 0) {
    int topcnt = 0;
    // top left
    if (i > 0 && std::isdigit(v[j - 1][i - 1])) {
      topcnt++;
      std::println("Top left");
    }
    // top center
    if (std::isdigit(v[j - 1][i])) {
      std::println("Top");
      topcnt++;
    }
    // top right
    if (i < n - 1 && std::isdigit(v[j - 1][i + 1])) {
      std::println("Top Right");
      topcnt++;
    }

    if (topcnt == 1 || topcnt == 3 ||
        (topcnt == 2 && std::isdigit(v[j - 1][i]))) {
      int a = i;
      for (; a > 0 && std::isdigit(v[j - 1][a - 1]); a--)
        ;
      for (; !std::isdigit(v[j - 1][a]); a++)
        ;

      int num = parseRight(v, j - 1, a);
      nums.push_back(num);
    } else if (topcnt == 2) {
      int num = parseLeft(v, j - 1, i - 1);
      nums.push_back(num);
      num = parseRight(v, j - 1, i + 1);
      nums.push_back(num);
    }
  }
  int m = v.size();
  // bottom
  if (j < m - 1) {
    int botcnt = 0;
    // bottom left
    if (i > 0 && std::isdigit(v[j + 1][i - 1])) {
      botcnt++;
      std::println("Bottom Left");
    }
    // bottom center
    if (std::isdigit(v[j + 1][i])) {
      botcnt++;
      std::println("Bottom");
    }
    // bottom right
    if (i < n - 1 && std::isdigit(v[j + 1][i + 1])) {
      botcnt++;
      std::println("Bottom Right");
    }
    if (botcnt == 1 || botcnt == 3 ||
        (botcnt == 2 && std::isdigit(v[j + 1][i]))) {
      int a = i;
      for (; a > 0 && std::isdigit(v[j + 1][a - 1]); a--)
        ;
      for (; !std::isdigit(v[j + 1][a]); a++)
        ;
      int num = parseRight(v, j + 1, a);
      nums.push_back(num);

    } else if (botcnt == 2) {
      int num = parseLeft(v, j + 1, i - 1);
      nums.push_back(num);
      num = parseRight(v, j + 1, i + 1);
      nums.push_back(num);
    }
  }

  return nums;
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
      if (v[j][i] == '*') {
        auto nums = consider(v, j, i);
        if (nums.size() == 2) {
          int value = nums[0] * nums[1];
          total += value;
          std::println("Found gear at ({0},{1}), {2} = {3}  * {4}", j, i, value,
                       nums[0], nums[1]);
        }
      }
    }
  }
  std::println("total: {0}", total);
}
