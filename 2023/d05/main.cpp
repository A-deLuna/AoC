#include <algorithm>
#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using inttype = long long;

struct range {
  inttype start;
  inttype count;
  inttype end() { return this->start + this->count - 1; }
  bool intercepts(range other) {
    return std::max(this->start, other.start) <=
           std::min(this->end(), other.end());
  }
};

std::ostream &operator<<(std::ostream &o, range r) {
  return o << "{start=" << r.start << ", count=" << r.count << "}";
}

template <typename T>
std::ostream &operator<<(std::ostream &o, std::vector<T> t) {
  o << "{";
  for (auto v : t) {
    o << v << ",";
  }
  return o << "}";
}

int main() {
  std::string s;
  std::cin >> s;
  std::vector<range> seeds;
  inttype n, m;
  while (std::cin >> n >> m) {
    seeds.push_back(range{.start = n, .count = m});
  }
  std::cout << "parsed seeds:" << seeds << "\n";
  std::cin.clear();
  while (std::getline(std::cin, s)) {
    if (s == "\n")
      continue;

    std::cout << s << "\n";
    inttype from, to, count;
    std::vector<range> newSeeds;
    while (std::cin >> to >> from >> count) {
      std::println("maps: {0}, {1}, {2}", from, to, count);
      for (int i = 0; i < seeds.size(); i++) {
        range other{.start = from, .count = count};
        if (seeds[i].intercepts(other)) {
          std::cout << "Seed " << seeds[i] << " intercepts " << other << "\n";
          // if I have unmapped zone at the start
          if (seeds[i].start < other.start) {
            auto r = range{.start = seeds[i].start,
                           .count = other.start - seeds[i].start};
            std::cout << "adding range " << r << '\n';
            seeds.push_back(r);
          }

          // if I have unmapped zone at the end
          if (other.end() < seeds[i].end()) {
            auto r = range{.start = other.end() + 1,
                           .count = seeds[i].end() - other.end()};
            std::cout << "adding range " << r << '\n';
            seeds.push_back(r);
          }

          // Overlap
          inttype start = std::max(seeds[i].start, other.start);
          inttype end = std::min(seeds[i].end(), other.end());
          inttype diff = start - from;
          auto r = range{.start = to + diff, .count = end - start + 1};
          std::cout << "adding range " << r << '\n';
          newSeeds.push_back(r);

          // delete seed
          seeds[i] = {-1, -1};
        }
      }
    }
    for (auto r : seeds) {
      if (r.start != -1 && r.count != -1) {
        std::cout << "copying range " << r << '\n';
        newSeeds.push_back(r);
      }
    }
    seeds = newSeeds;
    std::cin.clear();
  }

  auto min = std::ranges::min_element(
      seeds, [](range a, range b) { return a.start < b.start; });
  std::println("min: {0}", min->start);
}
