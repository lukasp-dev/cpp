#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int factor = 2;
    int total = 0;
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Example 1: Capture by Value [factor]
    // 'factor' is copied. If 'factor' changes outside later, the lambda keeps the old value.
    auto multiply_by_val = [factor](int n) {
        return n * factor; 
    };

    // Example 2: Capture by Reference [&total]
    // We can modify 'total' directly inside the lambda.
    std::for_each(numbers.begin(), numbers.end(), [&](int n) {
        total += n; // Modifies the actual 'total' variable outside
    });

    // Example 3: Mixed Capture [factor, &total]
    // 'factor' is read-only copy, 'total' is modifiable reference.
    auto mixed_capture = [factor, &total]() {
        total *= factor;
    };

    std::cout << "Sum: " << total << "\n"; // 15
    mixed_capture();
    std::cout << "Sum after doubling: " << total << "\n"; // 30

    return 0;
}