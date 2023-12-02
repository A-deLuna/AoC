# Day 1

Read on HN that problem 2 was difficult. Didn't want to get too
clever with my solution.


## Things learnt

* [c++17 deduction guide for std::array][0] is neat.
    * Hope over the next few days I get a chance to look closer into how deduction
      guides work. Feels like magic at this point.
* String views are a refreshing addition. Feels very similar to working with go slices.
* The `<print>` header (c++23) is amazing. Favorite addition so far.
* The way  `while (std::cin >> s) {` works is via an [explicit conversion function operator bool()][1]
    *  Since c++11 there seems to be rules for [contextual conversion to bools][2] in scenarios like:
        * `if, while, for`,  logical operators, and others.
        * I don't understand implicit and contextual conversions. Would be neat to learn more
          in the coming days.


 
[0]: https://en.cppreference.com/w/cpp/container/array/deduction_guides
[1]: https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
[2]: https://en.cppreference.com/w/cpp/language/implicit_conversion
