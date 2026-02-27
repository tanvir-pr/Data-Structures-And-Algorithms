# Week 1: Arrays, Mathematics & Complexity Analysis

## Overview
This week focuses on building strong foundations in arrays, mathematical concepts needed for DSA, and complexity analysis.

---

## Day 1-2: Arrays & Functions

### Topics to Cover

#### 1. Arrays Basics
- Declaration and initialization
- Accessing elements
- Array traversal
- Input/output operations

#### 2. Multidimensional Arrays
- 2D arrays (matrix)
- Row-major and column-major order
- Matrix operations

#### 3. Pass by Value vs Pass by Reference
- How arrays are passed to functions
- Pointer arithmetic with arrays

#### 4. Dynamic Memory Allocation
- `new` and `delete` operators
- Dynamic arrays
- Memory management

### Your Course Files
- `Batch-7-Introduction-to-Programming/Module 7/`
  - `array.c`
  - `array_initialization.c`
  - `array_input_and_output.c`
  - `sum_of_all_values_of_an_array.c`
  - `printing_reverse_of_an_array.c`

- `Batch-7-Introduction-to-Programming/Module 9/`
  - `insert.c`
  - `delete.c`
  - `reversing_an_array.c`
  - `copy_elements_of_2_arrays.c`
  - `swap.c`

### Practice Problems (Day 1-2)

1. **Easy:**
   - Find maximum and minimum in an array
   - Reverse an array
   - Count even and odd numbers
   - Find sum and average

2. **Medium:**
   - Rotate array by k positions
   - Remove duplicates from sorted array
   - Find second largest element
   - Move all zeros to end

3. **Challenge:**
   - Find missing number in array (1 to n)
   - Two sum problem
   - Kadane's algorithm (maximum subarray sum)

---

## Day 3-4: Mathematics for DSA

### Topics to Cover

#### 1. Bitwise Operators
- AND (&), OR (|), XOR (^)
- Left shift (<<), Right shift (>>)
- NOT (~)

#### 2. Bit Manipulation
- Check if number is power of 2
- Count set bits
- Toggle, set, clear specific bits
- XOR properties

#### 3. Prime Numbers
- Naive approach
- Sieve of Eratosthenes
- Optimized prime checking

#### 4. Square Root Algorithms
- Binary search approach
- Newton's method

#### 5. HCF/LCM
- Euclidean algorithm
- Extended Euclidean algorithm
- Relationship between HCF and LCM

### Your Course Files
- `Batch-7-Basic-Data-Structures/Module 1/`
  - Check for math-related implementations

### Practice Problems (Day 3-4)

1. **Bitwise:**
   - Check if ith bit is set
   - Count total set bits from 1 to n
   - Find single number (all others appear twice)
   - Power of 2 check

2. **Mathematics:**
   - Print all primes up to n (Sieve)
   - Find GCD and LCM
   - Count digits in a number
   - Check if number is palindrome
   - Find all divisors of a number

---

## Day 5-7: Time & Space Complexity

### Topics to Cover

#### 1. Asymptotic Notation
- Big O (O) - Upper bound
- Big Omega (Ω) - Lower bound
- Big Theta (Θ) - Tight bound

#### 2. Common Time Complexities
- O(1) - Constant
- O(log n) - Logarithmic
- O(n) - Linear
- O(n log n) - Linearithmic
- O(n²) - Quadratic
- O(2ⁿ) - Exponential
- O(n!) - Factorial

#### 3. Space Complexity
- Auxiliary space vs total space
- In-place algorithms
- Recursive call stack space

#### 4. Best, Worst, Average Cases
- Understanding different scenarios
- Amortized analysis basics

### Your Course Files
- `Batch-7-Basic-Data-Structures/Module 1/`
  - `space_complexity.cpp`
  - `sqrt_complexity_O_sqrtN.cpp`
  - `sum.cpp`

### Practice Exercises (Day 5-7)

Analyze time and space complexity of these:

```cpp
// Exercise 1
for(int i=0; i<n; i++) {
    cout << i;
}

// Exercise 2
for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
        cout << i << j;
    }
}

// Exercise 3
for(int i=1; i<=n; i*=2) {
    cout << i;
}

// Exercise 4
for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
        cout << i << j;
    }
}

// Exercise 5
int fib(int n) {
    if(n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

// Exercise 6
for(int i=1; i*i<=n; i++) {
    cout << i;
}

// Exercise 7
void solve(int n) {
    if(n == 0) return;
    solve(n-1);
    cout << n;
    solve(n-1);
}

// Exercise 8
for(int i=0; i<n; i++) {
    for(int j=i; j<n; j++) {
        for(int k=0; k<n; k++) {
            cout << i << j << k;
        }
    }
}

// Exercise 9
int binary_search(int arr[], int n, int x) {
    int l=0, r=n-1;
    while(l <= r) {
        int mid = (l+r)/2;
        if(arr[mid] == x) return mid;
        else if(arr[mid] < x) l = mid+1;
        else r = mid-1;
    }
    return -1;
}

// Exercise 10
void merge_sort(int arr[], int l, int r) {
    if(l >= r) return;
    int mid = (l+r)/2;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid+1, r);
    merge(arr, l, mid, r);
}
```

**Answers:** Write time and space complexity for each

---

## Week 1 Checklist

- [ ] Completed all theory videos/readings
- [ ] Typed and ran all code examples
- [ ] Solved minimum 20 problems
- [ ] Understood complexity analysis
- [ ] Made notes for revision
- [ ] Identified weak areas for next week

---

## Resources for Week 1

### Online Practice
- **LeetCode:** Array tag (Easy problems)
- **HackerRank:** Arrays and Math sections
- **Codeforces:** 800-1000 rated problems

### Key Concepts to Master
1. Array manipulation techniques
2. Two-pointer approach
3. Sliding window basics
4. Bitwise tricks
5. Prime number generation
6. Complexity calculation rules

---

## Notes Section

### Important Formulas:
- Sum of first n numbers: n(n+1)/2
- Sum of squares: n(n+1)(2n+1)/6
- XOR properties: a^a = 0, a^0 = a
- GCD(a,b) * LCM(a,b) = a * b

### Common Mistakes to Avoid:
- Array index out of bounds
- Integer overflow in calculations
- Not considering edge cases (empty array, single element)
- Confusing time vs space complexity

### Tips:
- Always dry run code with sample inputs
- Draw diagrams for 2D arrays
- Practice bit manipulation on paper first
- Memorize common complexity patterns

---

**End of Week 1 Plan**
