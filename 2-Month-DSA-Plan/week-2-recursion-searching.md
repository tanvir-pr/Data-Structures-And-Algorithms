# Week 2: Recursion & Searching Algorithms

## Overview
Master recursion thinking and implement efficient searching algorithms.

---

## Day 8-10: Recursion

### Topics to Cover

#### 1. Recursion Fundamentals
- What is recursion?
- Base case and recursive case
- How recursion works (call stack)
- When to use recursion

#### 2. Recursion Tree
- Drawing recursion trees
- Understanding time complexity through trees
- Recurrence relations

#### 3. Types of Recursion
- Direct vs Indirect recursion
- Tail recursion
- Head recursion
- Tree recursion

#### 4. Backtracking Introduction
- Exploring all possibilities
- Pruning branches

### Your Course Files
- `Batch-7-Introduction-to-Programming/Module 19/`
  - `J_Factorial.c`
  - `I_Count_Vowels.c`
  - `D_Print_Digits_using_Recursion.c`
  - `W_Mirror_Array.c`

### Practice Problems (Day 8-10)

#### Easy (4-5 problems)
1. Print 1 to N using recursion
2. Print N to 1 using recursion
3. Calculate factorial
4. Calculate power (x^n)
5. Sum of first N natural numbers

#### Medium (4-5 problems)
6. Fibonacci sequence (nth number)
7. Sum of digits using recursion
8. Reverse a string using recursion
9. Check if string is palindrome (recursive)
10. Count vowels in string (recursive)

#### Advanced (3-4 problems)
11. Tower of Hanoi
12. Generate all subsets of a set
13. Print all permutations of a string
14. Generate all binary strings of length n

### Key Concepts
```cpp
// Basic recursion template
void recursion(parameters) {
    // Base case
    if (base_condition) {
        return;
    }
    
    // Recursive case
    // Do some work
    recursion(modified_parameters);
    // Do some more work (if needed)
}

// Example: Factorial
int factorial(int n) {
    if (n == 0 || n == 1) return 1;  // Base case
    return n * factorial(n-1);        // Recursive case
}

// Example: Print 1 to N
void print(int n) {
    if (n == 0) return;    // Base case
    print(n-1);            // Recursive call
    cout << n << " ";      // Work after recursion
}
```

---

## Day 11-14: Searching Algorithms

### Topics to Cover

#### 1. Linear Search
- Sequential search
- Time complexity: O(n)
- When to use linear search

#### 2. Binary Search
- Prerequisite: Sorted array
- Iterative implementation
- Recursive implementation
- Time complexity: O(log n)

#### 3. Binary Search Applications
- Find first occurrence
- Find last occurrence
- Count occurrences
- Search in rotated sorted array
- Find peak element
- Square root using binary search

#### 4. Ternary Search
- Divide into three parts
- Finding maximum/minimum in unimodal function

### Your Course Files
- `Batch-7-Basic-Data-Structures/Module 3/`
  - `Z_Binary_Search.cpp` (check this file)

### Practice Problems (Day 11-14)

#### Linear Search (2-3 problems)
1. Search element in unsorted array
2. Find all occurrences of element
3. Search in 2D matrix (row-wise and column-wise unsorted)

#### Binary Search - Basic (5-6 problems)
4. Standard binary search
5. Find first occurrence of element
6. Find last occurrence of element
7. Count occurrences in sorted array
8. Search insert position
9. Find floor and ceiling

#### Binary Search - Advanced (6-8 problems)
10. Search in rotated sorted array
11. Find minimum in rotated sorted array
12. Find peak element
13. Square root using binary search
14. Aggressive cows problem
15. Book allocation problem
16. Painter's partition problem
17. Find median of two sorted arrays

#### Ternary Search (2 problems)
18. Find maximum in unimodal array
19. Minimize function using ternary search

### Key Implementations

#### Linear Search
```cpp
int linearSearch(int arr[], int n, int target) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == target) {
            return i;
        }
    }
    return -1;
}
```

#### Binary Search - Iterative
```cpp
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(arr[mid] == target) {
            return mid;
        }
        else if(arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}
```

#### Binary Search - Recursive
```cpp
int binarySearchRecursive(int arr[], int left, int right, int target) {
    if(left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    if(arr[mid] == target) {
        return mid;
    }
    else if(arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, right, target);
    }
    else {
        return binarySearchRecursive(arr, left, mid - 1, target);
    }
}
```

#### First Occurrence
```cpp
int firstOccurrence(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching in left half
        }
        else if(arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return result;
}
```

#### Last Occurrence
```cpp
int lastOccurrence(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching in right half
        }
        else if(arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return result;
}
```

---

## Day 3-4: Mathematics

### Topics to Cover

#### 1. Bitwise Operations
```cpp
// Check if ith bit is set
bool isSet(int n, int i) {
    return (n & (1 << i)) != 0;
}

// Set ith bit
int setBit(int n, int i) {
    return n | (1 << i);
}

// Clear ith bit
int clearBit(int n, int i) {
    return n & ~(1 << i);
}

// Toggle ith bit
int toggleBit(int n, int i) {
    return n ^ (1 << i);
}

// Count set bits
int countSetBits(int n) {
    int count = 0;
    while(n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Check power of 2
bool isPowerOf2(int n) {
    return n > 0 && (n & (n-1)) == 0;
}
```

#### 2. Prime Numbers
```cpp
// Check if prime (O(√n))
bool isPrime(int n) {
    if(n <= 1) return false;
    if(n <= 3) return true;
    if(n % 2 == 0 || n % 3 == 0) return false;
    
    for(int i = 5; i * i <= n; i += 6) {
        if(n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Sieve of Eratosthenes
void sieve(int n) {
    vector<bool> prime(n+1, true);
    prime[0] = prime[1] = false;
    
    for(int i = 2; i * i <= n; i++) {
        if(prime[i]) {
            for(int j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }
    
    // Print all primes
    for(int i = 2; i <= n; i++) {
        if(prime[i]) cout << i << " ";
    }
}
```

#### 3. GCD/LCM
```cpp
// Euclidean algorithm for GCD
int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

// LCM using GCD
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
```

### Practice Problems (Day 3-4)

1. Find XOR of all elements in array
2. Find two non-repeating elements in array
3. Count primes up to n
4. Find nth prime number
5. Calculate a^b mod m efficiently
6. Find all prime factors of a number
7. Count trailing zeros in factorial

---

## Day 5-7: Complexity Analysis Practice

### Exercises

For each code snippet, determine:
- Time Complexity
- Space Complexity
- Best/Worst case scenarios

### Problem Set

1. **Array traversal:** O(?)
2. **Nested loops (n×n):** O(?)
3. **Binary search:** O(?)
4. **Merge sort:** O(?)
5. **Fibonacci (naive recursion):** O(?)
6. **Loop with i*=2:** O(?)
7. **Loop with i+=√n:** O(?)
8. **Three nested loops:** O(?)

### Complexity Comparison Table

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| Linear Search | O(1) | O(n) | O(n) | O(1) |
| Binary Search | O(1) | O(log n) | O(log n) | O(1) |
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) |

---

## Week 1 Summary

### What You Should Know
- ✅ Array operations and manipulations
- ✅ Bitwise operations and tricks
- ✅ Prime number algorithms
- ✅ GCD/LCM calculations
- ✅ Recursion thinking
- ✅ Binary search and variants
- ✅ Time/space complexity analysis

### Problems Solved Target: 25-30

### Next Week Preview
Week 2 will cover sorting algorithms - building on your array and complexity knowledge.

---

## Daily Study Tips

1. **Morning:** Theory (1 hour)
2. **Afternoon:** Implementation (1 hour)
3. **Evening:** Problem solving (1.5-2 hours)
4. **Before Sleep:** Quick revision (15 min)

**Remember:** Understanding > Speed. Take time to understand why an algorithm works!
