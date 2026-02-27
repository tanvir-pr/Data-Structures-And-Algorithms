# Week 3: Sorting Algorithms

## Overview
Master all major sorting algorithms, understand their complexities, and know when to use each.

---

## Day 15-17: Basic Sorting Algorithms

### Day 15: Bubble Sort

#### Concept
- Compare adjacent elements and swap if needed
- Largest element "bubbles up" to the end
- Repeat until array is sorted

#### Implementation
```cpp
void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        bool swapped = false;
        
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        
        // Optimization: if no swap, array is sorted
        if(!swapped) break;
    }
}
```

#### Complexity
- **Time:** Best O(n), Average O(n²), Worst O(n²)
- **Space:** O(1)
- **Stable:** Yes
- **In-place:** Yes

#### When to Use
- Small datasets
- Nearly sorted arrays
- Educational purposes

---

### Day 16: Selection Sort

#### Concept
- Find minimum element and place it at beginning
- Repeat for remaining unsorted portion
- Divides array into sorted and unsorted parts

#### Implementation
```cpp
void selectionSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        int minIdx = i;
        
        // Find minimum in unsorted part
        for(int j = i+1; j < n; j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        
        // Swap minimum with first unsorted element
        if(minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}
```

#### Complexity
- **Time:** Best O(n²), Average O(n²), Worst O(n²)
- **Space:** O(1)
- **Stable:** No (can be made stable)
- **In-place:** Yes

#### When to Use
- Small datasets
- When memory writes are costly
- When simplicity is preferred

---

### Day 17: Insertion Sort

#### Concept
- Build sorted array one element at a time
- Pick element and insert at correct position
- Like sorting playing cards in hand

#### Implementation
```cpp
void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        
        arr[j+1] = key;
    }
}
```

#### Complexity
- **Time:** Best O(n), Average O(n²), Worst O(n²)
- **Space:** O(1)
- **Stable:** Yes
- **In-place:** Yes

#### When to Use
- Small datasets
- Nearly sorted arrays
- Online sorting (elements arrive one by one)

---

## Day 18-21: Advanced Sorting Algorithms

### Day 18: Merge Sort

#### Concept
- Divide and conquer approach
- Divide array into halves recursively
- Merge sorted halves

#### Implementation
```cpp
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[n1], R[n2];
    
    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
```

#### Complexity
- **Time:** Best O(n log n), Average O(n log n), Worst O(n log n)
- **Space:** O(n)
- **Stable:** Yes
- **In-place:** No

#### When to Use
- Large datasets
- Need guaranteed O(n log n)
- External sorting
- When stability is required

---

### Day 19: Quick Sort

#### Concept
- Divide and conquer
- Choose pivot element
- Partition array around pivot
- Recursively sort partitions

#### Implementation
```cpp
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i+1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

#### Complexity
- **Time:** Best O(n log n), Average O(n log n), Worst O(n²)
- **Space:** O(log n) - recursion stack
- **Stable:** No
- **In-place:** Yes

#### Optimization: Randomized Quick Sort
```cpp
int randomPartition(int arr[], int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(arr[random], arr[high]);
    return partition(arr, low, high);
}
```

#### When to Use
- General purpose sorting
- Average case O(n log n) is acceptable
- In-place sorting needed

---

### Day 20: Counting Sort

#### Concept
- Non-comparison based sort
- Count frequency of each element
- Calculate positions
- Works when range is known and small

#### Implementation
```cpp
void countingSort(int arr[], int n) {
    int maxVal = *max_element(arr, arr + n);
    int minVal = *min_element(arr, arr + n);
    int range = maxVal - minVal + 1;
    
    vector<int> count(range, 0);
    vector<int> output(n);
    
    // Count frequencies
    for(int i = 0; i < n; i++) {
        count[arr[i] - minVal]++;
    }
    
    // Calculate cumulative count
    for(int i = 1; i < range; i++) {
        count[i] += count[i-1];
    }
    
    // Build output array
    for(int i = n-1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }
    
    // Copy to original array
    for(int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}
```

#### Complexity
- **Time:** O(n + k) where k is range
- **Space:** O(n + k)
- **Stable:** Yes
- **In-place:** No

---

### Day 21: Radix Sort & Bucket Sort

#### Radix Sort

**Concept:** Sort digit by digit using counting sort

```cpp
void countingSortForRadix(int arr[], int n, int exp) {
    vector<int> output(n);
    vector<int> count(10, 0);
    
    for(int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    
    for(int i = 1; i < 10; i++) {
        count[i] += count[i-1];
    }
    
    for(int i = n-1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    for(int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    int maxVal = *max_element(arr, arr + n);
    
    for(int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp);
    }
}
```

**Complexity:**
- **Time:** O(d × (n + k)) where d is digits, k is base
- **Space:** O(n + k)

---

#### Bucket Sort

**Concept:** Distribute elements into buckets, sort each bucket

```cpp
void bucketSort(float arr[], int n) {
    vector<vector<float>> buckets(n);
    
    // Put elements in buckets
    for(int i = 0; i < n; i++) {
        int bucketIdx = n * arr[i];
        buckets[bucketIdx].push_back(arr[i]);
    }
    
    // Sort individual buckets
    for(int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    // Concatenate buckets
    int index = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}
```

**Complexity:**
- **Time:** Average O(n + k), Worst O(n²)
- **Space:** O(n + k)

---

## Sorting Algorithm Comparison

| Algorithm | Best | Average | Worst | Space | Stable | In-place |
|-----------|------|---------|-------|-------|--------|----------|
| Bubble | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | No | Yes |
| Insertion | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |
| Merge | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes | No |
| Quick | O(n log n) | O(n log n) | O(n²) | O(log n) | No | Yes |
| Counting | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes | No |
| Radix | O(d(n+k)) | O(d(n+k)) | O(d(n+k)) | O(n+k) | Yes | No |
| Bucket | O(n+k) | O(n+k) | O(n²) | O(n) | Yes | No |

---

## When to Use Which Sort?

### Use Bubble Sort when:
- Array is nearly sorted
- Teaching/learning purposes
- Very small arrays (< 10 elements)

### Use Selection Sort when:
- Memory writes are expensive
- Small arrays
- Simplicity is priority

### Use Insertion Sort when:
- Array is nearly sorted
- Small arrays
- Online sorting needed
- As part of hybrid algorithms (Timsort)

### Use Merge Sort when:
- Stability is required
- Guaranteed O(n log n) needed
- External sorting (large data on disk)
- Linked list sorting

### Use Quick Sort when:
- Average case O(n log n) is acceptable
- In-place sorting needed
- General purpose sorting
- Random access is fast

### Use Counting Sort when:
- Range of elements is small
- Elements are integers
- Need linear time

### Use Radix Sort when:
- Sorting integers or strings
- Range is large but number of digits is small

### Use Bucket Sort when:
- Input is uniformly distributed
- Floating point numbers

---

## Practice Problems (Week 3)

### Day 15: Bubble Sort (3 problems)
1. Implement bubble sort
2. Count swaps in bubble sort
3. Sort array with minimum swaps

### Day 16: Selection Sort (3 problems)
4. Implement selection sort
5. Find kth smallest using selection sort idea
6. Minimum swaps to sort array

### Day 17: Insertion Sort (4 problems)
7. Implement insertion sort
8. Insertion sort for linked list
9. Count inversions using insertion sort
10. Sort nearly sorted array

### Day 18: Merge Sort (4 problems)
11. Implement merge sort
12. Count inversions (merge sort approach)
13. Merge k sorted arrays
14. Sort linked list using merge sort

### Day 19: Quick Sort (4 problems)
15. Implement quick sort
16. Kth smallest element (quick select)
17. Sort colors (Dutch flag - 3-way partition)
18. Nuts and bolts problem

### Day 20: Non-comparison Sorts (3 problems)
19. Sort array of 0s, 1s, 2s (counting sort)
20. Radix sort implementation
21. Sort array by frequency

### Day 21: Mixed Problems (5 problems)
22. Merge intervals
23. Largest number from array
24. Sort by absolute difference
25. Relative sort array
26. Minimum difference pairs

---

## Key Takeaways

### Comparison-based Sorts
- Cannot be faster than O(n log n) in worst case
- Bubble, Selection, Insertion are O(n²)
- Merge, Quick, Heap are O(n log n)

### Non-comparison Sorts
- Can achieve O(n) time
- Work on specific data types
- Require extra space

### Stability Matters When:
- Sorting objects with multiple keys
- Maintaining relative order is important

### In-place Matters When:
- Memory is limited
- Large datasets

---

## Sorting Problem Patterns

### Pattern 1: Direct Sorting
- Problem asks to sort array
- Use appropriate algorithm based on constraints

### Pattern 2: Partial Sorting
- Find kth smallest/largest
- Use Quick Select or Heap

### Pattern 3: Custom Comparator
- Sort by custom criteria
- Use STL sort with lambda

### Pattern 4: Counting/Frequency
- Sort by frequency
- Use hash map + sorting

### Pattern 5: Two Pointer After Sort
- Two sum, three sum
- Sort first, then use two pointers

---

## C++ STL Sorting

### Built-in Functions
```cpp
#include <algorithm>

// Sort in ascending order
sort(arr, arr + n);

// Sort in descending order
sort(arr, arr + n, greater<int>());

// Sort with custom comparator
sort(arr, arr + n, [](int a, int b) {
    return a > b;  // descending
});

// Partial sort (first k elements)
partial_sort(arr, arr + k, arr + n);

// Nth element (quick select)
nth_element(arr, arr + k, arr + n);

// Stable sort
stable_sort(arr, arr + n);
```

### For Vectors
```cpp
vector<int> v = {5, 2, 8, 1, 9};

sort(v.begin(), v.end());
stable_sort(v.begin(), v.end());
partial_sort(v.begin(), v.begin() + 3, v.end());
```

---

## Common Mistakes to Avoid

1. **Off-by-one errors** in loop bounds
2. **Not handling edge cases** (empty array, single element)
3. **Integer overflow** in mid calculation (use `left + (right-left)/2`)
4. **Not considering stability** when required
5. **Using wrong sort** for the problem constraints
6. **Forgetting to optimize** bubble sort with swapped flag

---

## Week 3 Checklist

- [ ] Implemented all 6+ sorting algorithms from scratch
- [ ] Understood time/space complexity of each
- [ ] Know when to use which algorithm
- [ ] Solved 20-25 sorting problems
- [ ] Can explain stability and in-place concepts
- [ ] Practiced with C++ STL sort functions

---

## Revision Tips

1. **Create comparison chart** of all algorithms
2. **Trace each algorithm** with sample array [5, 2, 8, 1, 9]
3. **Identify patterns** in problems
4. **Practice without looking** at code
5. **Explain to someone** (rubber duck debugging)

---

**Next Week:** Linked Lists - applying your sorting knowledge to linked structures!
