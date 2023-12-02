# Day 2

Today's problem was pretty straightforward. Parsing the input was the only
interesting part.

I didn't find any c++20 or c++23 additions that helped simplify the parsing
 code for this.


## Things learnt
While browsing cppreference I noticed c++26 will allow stringstream to
be initialized from a string view. That would've been useful in this problem
to avoid a copy when initializing the stringstream.
