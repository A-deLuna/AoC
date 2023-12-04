# Day 4

Problem was simpler than last couple of days.

## Things learnt

I was surprised that calling `operator>>(stream, int)` will fail when the stream contains ': 1234" or "| 1234". I don't know why I believed the leading extraneous character would automatically be consumed.

Also my code for calculating power of twos had an off-by-one error.

```c++
for (i = 1; have > 0; have--, i *= 2);
```

Or rather, my code calculated power of twos but the problem required 2^n-1.
