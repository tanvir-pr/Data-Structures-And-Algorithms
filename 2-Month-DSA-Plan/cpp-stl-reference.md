# C++ STL Quick Reference for DSA

## Overview
The Standard Template Library (STL) is crucial for efficient DSA problem-solving. This reference covers commonly used containers and algorithms.

---

## Containers

### 1. Vector (Dynamic Array)

```cpp
#include <vector>

// Declaration
vector<int> v;
vector<int> v(10);           // size 10, default value 0
vector<int> v(10, 5);        // size 10, all elements = 5
vector<int> v = {1, 2, 3};   // initialization list

// Common Operations
v.push_back(10);             // Add at end - O(1) amortized
v.pop_back();                // Remove from end - O(1)
v.size();                    // Number of elements - O(1)
v.empty();                   // Check if empty - O(1)
v.clear();                   // Remove all elements - O(n)
v.front();                   // First element - O(1)
v.back();                    // Last element - O(1)
v[i];                        // Access ith element - O(1)
v.at(i);                     // Access with bounds checking - O(1)

// Insertion/Deletion
v.insert(v.begin() + i, val);    // Insert at position i - O(n)
v.erase(v.begin() + i);          // Erase at position i - O(n)

// Iteration
for(int x : v) { }               // Range-based for loop
for(auto it = v.begin(); it != v.end(); it++) { }

// Useful functions
reverse(v.begin(), v.end());
sort(v.begin(), v.end());
```

**Time Complexity:**
- Access: O(1)
- Insert/Delete at end: O(1) amortized
- Insert/Delete at middle: O(n)
- Search: O(n)

---

### 2. Stack

```cpp
#include <stack>

stack<int> s;

// Operations
s.push(10);                  // Push element - O(1)
s.pop();                     // Pop element - O(1)
s.top();                     // Get top element - O(1)
s.empty();                   // Check if empty - O(1)
s.size();                    // Get size - O(1)
```

**Use Cases:**
- Expression evaluation
- Parenthesis matching
- Backtracking
- DFS traversal

---

### 3. Queue

```cpp
#include <queue>

queue<int> q;

// Operations
q.push(10);                  // Enqueue - O(1)
q.pop();                     // Dequeue - O(1)
q.front();                   // Get front element - O(1)
q.back();                    // Get back element - O(1)
q.empty();                   // Check if empty - O(1)
q.size();                    // Get size - O(1)
```

**Use Cases:**
- BFS traversal
- Level order traversal
- Scheduling problems

---

### 4. Priority Queue (Heap)

```cpp
#include <queue>

// Max heap (default)
priority_queue<int> maxHeap;

// Min heap
priority_queue<int, vector<int>, greater<int>> minHeap;

// Operations
pq.push(10);                 // Insert - O(log n)
pq.pop();                    // Remove top - O(log n)
pq.top();                    // Get top element - O(1)
pq.empty();                  // Check if empty - O(1)
pq.size();                   // Get size - O(1)

// Custom comparator
auto cmp = [](int a, int b) { return a > b; };
priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
```

**Use Cases:**
- Kth largest/smallest element
- Merge k sorted arrays
- Dijkstra's algorithm
- Huffman coding

---

### 5. Set

```cpp
#include <set>

set<int> s;                  // Sorted, unique elements

// Operations
s.insert(10);                // Insert - O(log n)
s.erase(10);                 // Remove element - O(log n)
s.find(10);                  // Find element - O(log n)
s.count(10);                 // Check existence (0 or 1) - O(log n)
s.size();                    // Size - O(1)
s.empty();                   // Check if empty - O(1)
s.clear();                   // Clear all - O(n)

// Access
*s.begin();                  // First element
*s.rbegin();                 // Last element

// Iteration
for(int x : s) { }           // In sorted order
```

**Use Cases:**
- Remove duplicates
- Maintain sorted order
- Range queries

---

### 6. Multiset

```cpp
#include <set>

multiset<int> ms;            // Sorted, allows duplicates

// Same operations as set
ms.insert(10);
ms.erase(10);                // Removes ALL occurrences
ms.erase(ms.find(10));       // Removes ONE occurrence
ms.count(10);                // Count occurrences - O(log n + count)
```

**Use Cases:**
- When duplicates are needed
- Frequency-based problems

---

### 7. Map

```cpp
#include <map>

map<int, int> m;             // Sorted by key

// Operations
m[key] = value;              // Insert/Update - O(log n)
m.insert({key, value});      // Insert - O(log n)
m.erase(key);                // Remove - O(log n)
m.find(key);                 // Find - O(log n)
m.count(key);                // Check existence (0 or 1) - O(log n)
m.size();                    // Size - O(1)

// Access
m[key];                      // Access value (creates if not exists)
m.at(key);                   // Access with exception if not exists

// Iteration
for(auto& [key, val] : m) {
    cout << key << " " << val << endl;
}
```

**Use Cases:**
- Frequency counting
- Mapping relationships
- Coordinate compression

---

### 8. Unordered Map (Hash Map)

```cpp
#include <unordered_map>

unordered_map<int, int> um;  // Not sorted, faster

// Operations (same as map)
um[key] = value;             // Insert/Update - O(1) average
um.insert({key, value});     // Insert - O(1) average
um.erase(key);               // Remove - O(1) average
um.find(key);                // Find - O(1) average
um.count(key);               // Check existence - O(1) average
```

**Time Complexity:**
- Average: O(1)
- Worst: O(n) - rare, due to collisions

**Use Cases:**
- When order doesn't matter
- Need faster operations
- Two sum, subarray sum problems

---

### 9. Unordered Set (Hash Set)

```cpp
#include <unordered_set>

unordered_set<int> us;

// Operations
us.insert(10);               // O(1) average
us.erase(10);                // O(1) average
us.find(10);                 // O(1) average
us.count(10);                // O(1) average
```

**Use Cases:**
- Fast lookup
- Remove duplicates (when order doesn't matter)

---

### 10. Deque (Double-Ended Queue)

```cpp
#include <deque>

deque<int> dq;

// Operations
dq.push_back(10);            // Add at end - O(1)
dq.push_front(10);           // Add at front - O(1)
dq.pop_back();               // Remove from end - O(1)
dq.pop_front();              // Remove from front - O(1)
dq.front();                  // First element - O(1)
dq.back();                   // Last element - O(1)
dq[i];                       // Random access - O(1)
```

**Use Cases:**
- Sliding window problems
- When need both stack and queue operations

---

### 11. Pair

```cpp
#include <utility>

pair<int, int> p;
p = {10, 20};
p = make_pair(10, 20);

// Access
p.first;
p.second;

// Comparison (lexicographic)
pair<int, int> p1 = {1, 2};
pair<int, int> p2 = {1, 3};
// p1 < p2 is true
```

---

## Algorithms

### 1. Sorting

```cpp
#include <algorithm>

// Sort in ascending order
sort(arr, arr + n);
sort(v.begin(), v.end());

// Sort in descending order
sort(arr, arr + n, greater<int>());

// Custom comparator
sort(v.begin(), v.end(), [](int a, int b) {
    return a > b;  // descending
});

// Stable sort (maintains relative order)
stable_sort(v.begin(), v.end());

// Partial sort (first k elements sorted)
partial_sort(v.begin(), v.begin() + k, v.end());

// Check if sorted
is_sorted(v.begin(), v.end());
```

---

### 2. Binary Search

```cpp
// Binary search (returns true/false)
binary_search(v.begin(), v.end(), target);

// Lower bound (first element >= target)
auto it = lower_bound(v.begin(), v.end(), target);
int index = it - v.begin();

// Upper bound (first element > target)
auto it = upper_bound(v.begin(), v.end(), target);

// Count occurrences
int count = upper_bound(v.begin(), v.end(), target) 
          - lower_bound(v.begin(), v.end(), target);
```

---

### 3. Min/Max

```cpp
// Min and max element
int minVal = *min_element(arr, arr + n);
int maxVal = *max_element(arr, arr + n);

// Min and max value
int minimum = min(a, b);
int maximum = max(a, b);

// Min/max of multiple values (C++11)
int result = min({a, b, c, d});
```

---

### 4. Reverse

```cpp
// Reverse array/vector
reverse(arr, arr + n);
reverse(v.begin(), v.end());

// Reverse string
string s = "hello";
reverse(s.begin(), s.end());
```

---

### 5. Accumulate (Sum)

```cpp
#include <numeric>

// Sum of all elements
int sum = accumulate(v.begin(), v.end(), 0);

// Product
int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
```

---

### 6. Count

```cpp
// Count occurrences
int cnt = count(v.begin(), v.end(), target);

// Count if (with condition)
int cnt = count_if(v.begin(), v.end(), [](int x) {
    return x > 10;
});
```

---

### 7. Find

```cpp
// Find element
auto it = find(v.begin(), v.end(), target);
if(it != v.end()) {
    // Found at position: it - v.begin()
}

// Find if (with condition)
auto it = find_if(v.begin(), v.end(), [](int x) {
    return x > 10;
});
```

---

### 8. Next/Prev Permutation

```cpp
// Next permutation
next_permutation(v.begin(), v.end());

// Previous permutation
prev_permutation(v.begin(), v.end());

// Generate all permutations
sort(v.begin(), v.end());
do {
    // Process current permutation
} while(next_permutation(v.begin(), v.end()));
```

---

### 9. Unique

```cpp
// Remove consecutive duplicates
sort(v.begin(), v.end());
auto it = unique(v.begin(), v.end());
v.erase(it, v.end());

// Or in one line
v.erase(unique(v.begin(), v.end()), v.end());
```

---

### 10. Swap

```cpp
// Swap two values
swap(a, b);

// Swap two vectors
swap(v1, v2);
```

---

## String Operations

```cpp
#include <string>

string s = "hello";

// Length
s.length();
s.size();

// Access
s[i];
s.at(i);

// Modify
s.push_back('x');
s.pop_back();
s += "world";

// Substring
s.substr(start, length);

// Find
s.find("ll");                // Returns index or string::npos
s.rfind("l");                // Find from right

// Compare
s1.compare(s2);              // Returns 0 if equal

// Convert
stoi("123");                 // String to int
to_string(123);              // Int to string
```

---

## Useful Patterns

### 1. Two Pointers
```cpp
int left = 0, right = n - 1;
while(left < right) {
    // Process
    if(condition) left++;
    else right--;
}
```

---

### 2. Sliding Window
```cpp
int windowSum = 0;
for(int i = 0; i < k; i++) {
    windowSum += arr[i];
}

int maxSum = windowSum;
for(int i = k; i < n; i++) {
    windowSum += arr[i] - arr[i-k];
    maxSum = max(maxSum, windowSum);
}
```

---

### 3. Frequency Map
```cpp
unordered_map<int, int> freq;
for(int x : arr) {
    freq[x]++;
}
```

---

### 4. Prefix Sum
```cpp
vector<int> prefix(n+1, 0);
for(int i = 0; i < n; i++) {
    prefix[i+1] = prefix[i] + arr[i];
}

// Sum from i to j
int sum = prefix[j+1] - prefix[i];
```

---

### 5. Fast I/O (Competitive Programming)
```cpp
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);
```

---

## Comparators

### Sort in Descending Order
```cpp
sort(v.begin(), v.end(), greater<int>());
```

### Custom Comparator (Lambda)
```cpp
// Sort by absolute value
sort(v.begin(), v.end(), [](int a, int b) {
    return abs(a) < abs(b);
});

// Sort pairs by second element
vector<pair<int, int>> vp;
sort(vp.begin(), vp.end(), [](auto& a, auto& b) {
    return a.second < b.second;
});
```

### Comparator Function
```cpp
bool compare(int a, int b) {
    return a > b;  // descending
}

sort(v.begin(), v.end(), compare);
```

---

## Iterator Operations

```cpp
vector<int> v = {1, 2, 3, 4, 5};

auto it = v.begin();         // Points to first element
auto it = v.end();           // Points past last element
auto it = v.rbegin();        // Reverse iterator (last element)
auto it = v.rend();          // Reverse iterator (before first)

// Advance iterator
advance(it, 3);              // Move iterator by 3 positions

// Distance between iterators
int dist = distance(v.begin(), v.end());

// Next and prev
auto next_it = next(it);
auto prev_it = prev(it);
```

---

## Common Mistakes to Avoid

1. **Using `v[i]` without checking size**
   - Use `v.at(i)` for bounds checking

2. **Modifying container while iterating**
   ```cpp
   // Wrong
   for(auto it = v.begin(); it != v.end(); it++) {
       v.erase(it);  // Invalidates iterator
   }
   
   // Correct
   for(auto it = v.begin(); it != v.end(); ) {
       if(condition) {
           it = v.erase(it);
       } else {
           it++;
       }
   }
   ```

3. **Not checking if map key exists**
   ```cpp
   // Wrong (creates key if not exists)
   if(m[key] == value) { }
   
   // Correct
   if(m.find(key) != m.end() && m[key] == value) { }
   ```

4. **Using map when unordered_map is better**
   - Use unordered_map for O(1) operations when order doesn't matter

5. **Forgetting to include headers**
   - Each STL component needs its header

---

## Time Complexity Cheat Sheet

| Container | Insert | Delete | Search | Access |
|-----------|--------|--------|--------|--------|
| Vector | O(1) end, O(n) middle | O(1) end, O(n) middle | O(n) | O(1) |
| Stack | O(1) | O(1) | - | O(1) top |
| Queue | O(1) | O(1) | - | O(1) front/back |
| Priority Queue | O(log n) | O(log n) | - | O(1) top |
| Set | O(log n) | O(log n) | O(log n) | - |
| Unordered Set | O(1) avg | O(1) avg | O(1) avg | - |
| Map | O(log n) | O(log n) | O(log n) | O(log n) |
| Unordered Map | O(1) avg | O(1) avg | O(1) avg | O(1) avg |

---

## When to Use What?

### Need fast access by index?
→ **Vector**

### Need LIFO (Last In First Out)?
→ **Stack**

### Need FIFO (First In First Out)?
→ **Queue**

### Need min/max element quickly?
→ **Priority Queue**

### Need sorted unique elements?
→ **Set**

### Need sorted elements with duplicates?
→ **Multiset**

### Need key-value pairs (sorted)?
→ **Map**

### Need key-value pairs (fast, unsorted)?
→ **Unordered Map**

### Need both ends operations?
→ **Deque**

---

## Pro Tips

1. **Use auto keyword**
   ```cpp
   auto it = v.begin();
   for(auto& x : v) { }
   ```

2. **Use emplace instead of push**
   ```cpp
   v.emplace_back(10);      // Slightly faster than push_back
   ```

3. **Reserve capacity for vectors**
   ```cpp
   v.reserve(1000);         // Avoid reallocation
   ```

4. **Use const reference in loops**
   ```cpp
   for(const auto& x : v) { }  // Avoid copying
   ```

5. **Clear vs Shrink**
   ```cpp
   v.clear();               // Removes elements, keeps capacity
   v.shrink_to_fit();       // Reduces capacity
   ```

---

## Practice Problems Using STL

1. Two sum using unordered_map
2. Top k frequent elements using priority queue
3. Sliding window maximum using deque
4. LRU cache using map + doubly linked list
5. Group anagrams using map
6. Longest consecutive sequence using set
7. Find duplicates using set
8. Merge intervals using vector + sort
9. Valid parentheses using stack
10. First non-repeating character using queue + map

---

## Additional Resources

- **C++ Reference:** https://cppreference.com/
- **STL Documentation:** https://www.cplusplus.com/reference/stl/
- **Practice:** Solve problems using STL instead of manual implementation

---

**Remember:** STL makes your code cleaner and faster. Master it for competitive programming and interviews!
