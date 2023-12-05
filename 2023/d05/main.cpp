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

// Uses ranges to keep track of the original seeds, and all the transformations that occur
// on them.
// Mappings within <src>-to-<dst> are also represented as ranges. For every mapping we iterate
// over all existing ranges of things. For the few ranges of things that overlap with the mapping
// we transform the values inside of the overlapping section and create new ranges for tracking
// non-overlapping sections separately.
// The code performs these tranformations and splitting of ranges on the fly as the input file is parsed.
// We can do this because the mappings are in order in the input file and we don't need them
// after transforming all the things.
int main() {
  std::string s;
  // parse 'seeds:'
  std::cin >> s;
  std::vector<range> seeds;
  inttype n, m;
  //read all the seed values.
  while (std::cin >> n >> m) {
    seeds.push_back(range{.start = n, .count = m});
  }
  std::cout << "parsed seeds:" << seeds << "\n";
  // allow to keep reading from std::cin after the previous error made it stop.
  std::cin.clear();

  while (std::getline(std::cin, s)) {
    if (s == "\n")
      continue;
    std::cout << s << "\n";

    inttype from, to, count;
    std::vector<range> newSeeds; // stores seeds after transformations.
    
    // read next set of transformations.
    while (std::cin >> to >> from >> count) {
      std::println("maps: {0}, {1}, {2}", from, to, count);

      // Check if any of the transformations apply to our "seeds" ranges.
      for (int i = 0; i < seeds.size(); i++) {
        range other{.start = from, .count = count};
        if (seeds[i].intercepts(other)) {
          std::cout << "Seed " << seeds[i] << " intercepts " << other << "\n";
          // There is a non-overlapping section at the beginning of the "seed".
          // Create a new range out of the non-overlapping section.
          if (seeds[i].start < other.start) {
            auto r = range{.start = seeds[i].start,
                           .count = other.start - seeds[i].start};
            std::cout << "adding range " << r << '\n';
            seeds.push_back(r);
          }

          // There is a non-overlapping section at the end of the "seed".
          // Create a new range out of the non-overlapping section.
          if (other.end() < seeds[i].end()) {
            auto r = range{.start = other.end() + 1,
                           .count = seeds[i].end() - other.end()};
            std::cout << "adding range " << r << '\n';
            seeds.push_back(r);
          }

          // Tranform the area that overlaps between the "seed" range and the mapping.
          inttype start = std::max(seeds[i].start, other.start);
          inttype end = std::min(seeds[i].end(), other.end());
          inttype diff = start - from;
          auto r = range{.start = to + diff, .count = end - start + 1};
          std::cout << "adding range " << r << '\n';
          newSeeds.push_back(r);

          // delete seed we processed.
          seeds[i] = {-1, -1};
        }
      }
    }
    // Some of the seeds ranges were not transformed. Copy those over.
    for (auto r : seeds) {
      if (r.start != -1 && r.count != -1) {
        std::cout << "copying range " << r << '\n';
        newSeeds.push_back(r);
      }
    }
    // delete all the previous ranges.
    seeds = std::move(newSeeds);
    std::cin.clear();
  }

  auto min = std::ranges::min_element(
      seeds, [](range a, range b) { return a.start < b.start; });
  std::println("min: {0}", min->start);
}
