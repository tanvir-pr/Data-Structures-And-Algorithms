# Week 7: Heaps, Graphs & Hashing

## Overview
Master heaps for priority operations, graphs for network problems, and hashing for fast lookups.

---

## Day 43-44: Heaps

### Day 43: Heap Basics

#### Concept
- **Complete Binary Tree** stored as array
- **Max Heap:** Parent ≥ Children
- **Min Heap:** Parent ≤ Children

#### Array Representation
```
For node at index i:
- Left child: 2*i + 1
- Right child: 2*i + 2
- Parent: (i-1)/2
```

---

#### Min Heap Implementation

```cpp
class MinHeap {
private:
    vector<int> heap;
    
    void heapifyUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(heap[parent] > heap[index]) {
                swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        
        while(index < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;
            
            if(left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if(right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }
            
            if(smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
    
public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMin() {
        if(heap.empty()) return -1;
        
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if(!heap.empty()) {
            heapifyDown(0);
        }
        
        return minVal;
    }
    
    int getMin() {
        return heap.empty() ? -1 : heap[0];
    }
    
    int size() {
        return heap.size();
    }
    
    bool empty() {
        return heap.empty();
    }
};
```

**Time Complexity:**
- Insert: O(log n)
- Extract Min/Max: O(log n)
- Get Min/Max: O(1)

---

#### Using C++ STL Priority Queue

```cpp
#include <queue>

// Max heap (default)
priority_queue<int> maxHeap;

// Min heap
priority_queue<int, vector<int>, greater<int>> minHeap;

maxHeap.push(10);        // O(log n)
maxHeap.pop();           // O(log n)
maxHeap.top();           // O(1)
maxHeap.empty();
maxHeap.size();
```

---

### Day 44: Heap Sort & Applications

#### Heap Sort

```cpp
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if(left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if(right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if(largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for(int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Extract elements one by one
    for(int i = n-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

**Time:** O(n log n)  
**Space:** O(1)

---

#### Applications

##### 1. Kth Largest Element

```cpp
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for(int num : nums) {
        minHeap.push(num);
        if(minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    return minHeap.top();
}
```

---

##### 2. Merge K Sorted Arrays

```cpp
vector<int> mergeKArrays(vector<vector<int>>& arrays) {
    vector<int> result;
    priority_queue<tuple<int, int, int>, 
                   vector<tuple<int, int, int>>, 
                   greater<tuple<int, int, int>>> minHeap;
    
    // Push first element of each array
    for(int i = 0; i < arrays.size(); i++) {
        if(!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }
    
    while(!minHeap.empty()) {
        auto [val, arrayIdx, elemIdx] = minHeap.top();
        minHeap.pop();
        
        result.push_back(val);
        
        if(elemIdx + 1 < arrays[arrayIdx].size()) {
            minHeap.push({arrays[arrayIdx][elemIdx + 1], arrayIdx, elemIdx + 1});
        }
    }
    
    return result;
}
```

---

##### 3. Top K Frequent Elements

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for(int num : nums) {
        freq[num]++;
    }
    
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> minHeap;
    
    for(auto& [num, count] : freq) {
        minHeap.push({count, num});
        if(minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    vector<int> result;
    while(!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    
    return result;
}
```

---

## Day 45-47: Graphs

### Day 45: Graph Representation

#### Graph Types
- **Directed:** Edges have direction
- **Undirected:** Edges are bidirectional
- **Weighted:** Edges have weights
- **Unweighted:** All edges equal

---

#### 1. Adjacency Matrix

```cpp
class Graph {
private:
    int V;  // Number of vertices
    vector<vector<int>> adjMatrix;
    
public:
    Graph(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
    }
    
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;  // For undirected graph
    }
    
    void display() {
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};
```

**Space:** O(V²)  
**Edge lookup:** O(1)  
**Good for:** Dense graphs

---

#### 2. Adjacency List

```cpp
class Graph {
private:
    int V;
    vector<vector<int>> adjList;
    
public:
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V);
    }
    
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // For undirected graph
    }
    
    void display() {
        for(int i = 0; i < V; i++) {
            cout << i << ": ";
            for(int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    vector<int> getNeighbors(int u) {
        return adjList[u];
    }
};
```

**Space:** O(V + E)  
**Edge lookup:** O(degree)  
**Good for:** Sparse graphs

---

### Day 46: Graph Traversal - BFS

#### Breadth-First Search (BFS)

```cpp
void BFS(vector<vector<int>>& adj, int start) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        
        for(int neighbor : adj[curr]) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
```

**Time:** O(V + E)  
**Space:** O(V)

---

#### BFS for All Components

```cpp
void BFSAll(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            BFS(adj, i, visited);
        }
    }
}

void BFS(vector<vector<int>>& adj, int start, vector<bool>& visited) {
    queue<int> q;
    visited[start] = true;
    q.push(start);
    
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        
        for(int neighbor : adj[curr]) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
```

---

#### Shortest Path in Unweighted Graph

```cpp
vector<int> shortestPath(vector<vector<int>>& adj, int start, int end) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        
        if(curr == end) break;
        
        for(int neighbor : adj[curr]) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }
    
    // Reconstruct path
    vector<int> path;
    int curr = end;
    while(curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());
    
    return path;
}
```

---

### Day 47: Graph Traversal - DFS

#### Depth-First Search (DFS)

**Recursive:**
```cpp
void DFS(vector<vector<int>>& adj, int curr, vector<bool>& visited) {
    visited[curr] = true;
    cout << curr << " ";
    
    for(int neighbor : adj[curr]) {
        if(!visited[neighbor]) {
            DFS(adj, neighbor, visited);
        }
    }
}

void DFSTraversal(vector<vector<int>>& adj, int start) {
    int n = adj.size();
    vector<bool> visited(n, false);
    DFS(adj, start, visited);
}
```

**Iterative:**
```cpp
void DFSIterative(vector<vector<int>>& adj, int start) {
    int n = adj.size();
    vector<bool> visited(n, false);
    stack<int> st;
    
    st.push(start);
    
    while(!st.empty()) {
        int curr = st.top();
        st.pop();
        
        if(!visited[curr]) {
            visited[curr] = true;
            cout << curr << " ";
            
            for(int neighbor : adj[curr]) {
                if(!visited[neighbor]) {
                    st.push(neighbor);
                }
            }
        }
    }
}
```

**Time:** O(V + E)  
**Space:** O(V)

---

#### Detect Cycle in Undirected Graph

```cpp
bool hasCycleDFS(vector<vector<int>>& adj, int curr, int parent, vector<bool>& visited) {
    visited[curr] = true;
    
    for(int neighbor : adj[curr]) {
        if(!visited[neighbor]) {
            if(hasCycleDFS(adj, neighbor, curr, visited)) {
                return true;
            }
        }
        else if(neighbor != parent) {
            return true;
        }
    }
    
    return false;
}

bool hasCycle(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            if(hasCycleDFS(adj, i, -1, visited)) {
                return true;
            }
        }
    }
    
    return false;
}
```

---

#### Detect Cycle in Directed Graph

```cpp
bool hasCycleDFS(vector<vector<int>>& adj, int curr, 
                 vector<bool>& visited, vector<bool>& recStack) {
    visited[curr] = true;
    recStack[curr] = true;
    
    for(int neighbor : adj[curr]) {
        if(!visited[neighbor]) {
            if(hasCycleDFS(adj, neighbor, visited, recStack)) {
                return true;
            }
        }
        else if(recStack[neighbor]) {
            return true;
        }
    }
    
    recStack[curr] = false;
    return false;
}

bool hasCycle(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            if(hasCycleDFS(adj, i, visited, recStack)) {
                return true;
            }
        }
    }
    
    return false;
}
```

---

#### Topological Sort (DFS)

```cpp
void topologicalSortDFS(vector<vector<int>>& adj, int curr, 
                        vector<bool>& visited, stack<int>& st) {
    visited[curr] = true;
    
    for(int neighbor : adj[curr]) {
        if(!visited[neighbor]) {
            topologicalSortDFS(adj, neighbor, visited, st);
        }
    }
    
    st.push(curr);
}

vector<int> topologicalSort(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    stack<int> st;
    
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            topologicalSortDFS(adj, i, visited, st);
        }
    }
    
    vector<int> result;
    while(!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    
    return result;
}
```

---

## Day 48-49: Hashing

### Day 48: Hash Tables Basics

#### Hash Map (C++ unordered_map)

```cpp
#include <unordered_map>

unordered_map<int, int> map;

// Insert/Update
map[key] = value;
map.insert({key, value});

// Access
int val = map[key];

// Check existence
if(map.find(key) != map.end()) { }
if(map.count(key) > 0) { }

// Delete
map.erase(key);

// Iterate
for(auto& [key, val] : map) {
    cout << key << " -> " << val << endl;
}
```

**Time:** O(1) average, O(n) worst

---

#### Hash Set (C++ unordered_set)

```cpp
#include <unordered_set>

unordered_set<int> set;

set.insert(10);
set.erase(10);
set.count(10);  // Returns 0 or 1
set.find(10) != set.end();
```

---

### Day 49: Hashing Applications

#### 1. Two Sum

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    
    for(int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        
        if(map.find(complement) != map.end()) {
            return {map[complement], i};
        }
        
        map[nums[i]] = i;
    }
    
    return {};
}
```

---

#### 2. Subarray with Sum 0

```cpp
bool hasZeroSumSubarray(vector<int>& arr) {
    unordered_set<int> prefixSums;
    int sum = 0;
    
    for(int num : arr) {
        sum += num;
        
        if(sum == 0 || prefixSums.count(sum)) {
            return true;
        }
        
        prefixSums.insert(sum);
    }
    
    return false;
}
```

---

#### 3. Longest Subarray with Sum K

```cpp
int longestSubarrayWithSumK(vector<int>& arr, int k) {
    unordered_map<int, int> prefixSumIndex;
    int sum = 0;
    int maxLen = 0;
    
    for(int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        
        if(sum == k) {
            maxLen = i + 1;
        }
        
        if(prefixSumIndex.find(sum - k) != prefixSumIndex.end()) {
            maxLen = max(maxLen, i - prefixSumIndex[sum - k]);
        }
        
        if(prefixSumIndex.find(sum) == prefixSumIndex.end()) {
            prefixSumIndex[sum] = i;
        }
    }
    
    return maxLen;
}
```

---

#### 4. Longest Consecutive Sequence

```cpp
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int maxLen = 0;
    
    for(int num : nums) {
        // Check if it's the start of a sequence
        if(numSet.find(num - 1) == numSet.end()) {
            int currentNum = num;
            int currentLen = 1;
            
            while(numSet.find(currentNum + 1) != numSet.end()) {
                currentNum++;
                currentLen++;
            }
            
            maxLen = max(maxLen, currentLen);
        }
    }
    
    return maxLen;
}
```

---

#### 5. Group Anagrams

```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> map;
    
    for(string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        map[key].push_back(s);
    }
    
    vector<vector<string>> result;
    for(auto& [key, group] : map) {
        result.push_back(group);
    }
    
    return result;
}
```

---

## Practice Problems (Week 7)

### Heaps (10 problems)

#### Day 43-44:
1. Implement min heap
2. Implement max heap
3. Heap sort
4. Kth largest element
5. Kth smallest element
6. Merge k sorted arrays
7. Top k frequent elements
8. Find median in stream
9. Merge k sorted linked lists
10. Sliding window median

---

### Graphs (12 problems)

#### Day 45: Representation (2)
11. Create adjacency list
12. Create adjacency matrix

#### Day 46: BFS (4)
13. BFS traversal
14. Shortest path in unweighted graph
15. Number of islands
16. Rotten oranges

#### Day 47: DFS (6)
17. DFS traversal
18. Detect cycle in undirected graph
19. Detect cycle in directed graph
20. Topological sort (DFS)
21. Number of connected components
22. Clone a graph

---

### Hashing (8 problems)

#### Day 48-49:
23. Two sum
24. First repeating element
25. Count distinct elements
26. Subarray with sum 0
27. Longest subarray with sum k
28. Longest consecutive sequence
29. Group anagrams
30. Longest substring without repeating

---

## Week 7 Checklist

- [ ] Implement min and max heap
- [ ] Understand heapify operation
- [ ] Master heap sort
- [ ] Implement graph using adjacency list
- [ ] Implement BFS and DFS
- [ ] Detect cycles in graphs
- [ ] Understand topological sort
- [ ] Master hash map operations
- [ ] Solve 30 problems

---

## Tips

1. **Heaps:** Use for top k problems
2. **BFS:** Use for shortest path
3. **DFS:** Use for connectivity
4. **Hashing:** Use for O(1) lookup
5. **Graph:** Choose right representation
6. **Visited array:** Prevent infinite loops

---

**Next Week:** Advanced algorithms and final revision!
