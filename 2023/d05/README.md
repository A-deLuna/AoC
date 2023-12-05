# Day 5

Part 2 had me struggling a lot more than previous days.

Took me a while to wrap my head around the logic for handling the different ranges. Also didn't
consider for a while that after splitting a range some sections still need to be considered by
rules we haven't seen yet.

Forgot to make a copy of solution 1. It was very similar to the code for part 2.

## Things learnt

### Designated initializers
The new designated initializer syntax is pretty cool.
```C++
range r{.start = 0, .count = 1};
```

Slowly my C++ feels more like Go. Or, should I say more like C?

### `<print>` behavior
Was a bit surprised to see that the `<print>` header can't print `std::vector`s by default.

I wonder what is the limitation for that. Luckily it's not that complex to implement it yourself
for iostream.
```C++
template <typename T>
std::ostream &operator<<(std::ostream &o, std::vector<T> v) {
  o << "{";
  for (auto a : v) {
    o << a << ",";
  }
  return o << "}";
}
```
Want to learn how to do the equivalent for functions in the new `<print>` header.


### Re-setting input stream
Another thing that caught me off-guard was having to reset the input stream with `std::cin.clear()`
after an error. We run into this when trying to parse the new lines and text after the last
number in a line. It's not super intuitive but it sort of makes sense that input streams preserve state
that allows callers to inspect the last error encountered when parsing.

### Int types
Got surprised by the input file containing numbers that don't fit in an `int`. Should get into the habit
of using `int64_t` or defining a type alias.
