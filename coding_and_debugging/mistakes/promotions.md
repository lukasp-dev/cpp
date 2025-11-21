### promotions
- definition: Promotion is a specific kind of implicit conversion that converts a value to a larger or more capable type without risk of data loss

1. int v. int -> int
2. smaller than int v. int -> int 
3. int v. floating-point -> floating point
4. unsigned int v. signed int -> unsigned int

### unsigned conversion (why x + 2^32)
- signed → unsigned uses modulo arithmetic (`x mod 2^32`)
- negative values become `(x + 2^32)` to produce a valid non-negative remainder
- example: -2 → -2 + 2^32 = 4294967294

### `size_t` promotion

- In C++, STL container functions like `size()` return **`size_t`**, which is an **unsigned integer type**.
- Unsigned arithmetic uses modulo \(2^N\), so values never go negative — they wrap around.
- Therefore, if a container is empty (`vec.size() == 0`) and you do:

  ```cpp
  vec.size() - 1
  ```
the result becomes:

2^32 - 1 on a 32-bit system 
2^64 - 1 on a 64-bit system

