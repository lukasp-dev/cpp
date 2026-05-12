## stdexcept

this header provides a set of standard exception classes ued to report logical and runtime errors, All standard exceptions derive from the base class `std::exception`.

### Two main categories
- `std::logic_error`(Developer Fault)

    - `out_of_range`: Thrown when an index or value exceeds its defined bounds(e.g., using `std::vector::at()` with an out-of-bounds index).
    - `invalid_argument`: Thrown when an actual parameter is not acceptable (e.g., passing a negative value to a function excepting only positives)

- `std::runtime_error` (Operational/External Fault):

    - `overflow_error` / `underflow_error`: Thrown when an arithmetic operation results in a value too large or too small for the destination type.
