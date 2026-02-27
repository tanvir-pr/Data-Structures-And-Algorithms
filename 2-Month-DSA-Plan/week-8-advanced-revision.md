# Week 8: Advanced Algorithms & Final Revision

## Overview
Learn advanced graph algorithms, dynamic programming basics, greedy algorithms, and comprehensive revision.

---

## Day 50-52: Advanced Graph Algorithms

### Day 50: Dijkstra's Algorithm (Shortest Path)

#### Concept
- Single-source shortest path
- Works with **non-negative** weights
- Uses priority queue (min heap)

#### Implementation

```cpp
vector<int> dijkstra(vector<vector<pair<int, int>>>& adj, int src) {
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> pq;
    
    dist[src] = 0;
    pq.push({0, src});  // {distance, node}
    
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if(d > dist[u]) continue;
        
        for(auto [v, weight] : adj[u]) {
            if(dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}
```

**Time:** O((V + E) log V)  
**Space:** O(V)

---

### Day 51: Minimum Spanning Tree (MST)

#### 1. Prim's Algorithm

```cpp
int primMST(vector<vector<pair<int, int>>>& adj) {
    int n = adj.size();
    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> pq;
    
    int mstWeight = 0;
    pq.push({0, 0});  // {weight, node}
    
    while(!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();
        
        if(inMST[u]) continue;
        
        inMST[u] = true;
        mstWeight += weight;
        
        for(auto [v, w] : adj[u]) {
            if(!inMST[v]) {
                pq.push({w, v});
            }
        }
    }
    
    return mstWeight;
}
```

**Time:** O((V + E) log V)

---

#### 2. Kruskal's Algorithm

```cpp
class DSU {
public:
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if(px == py) return false;
        
        if(rank[px] < rank[py]) {
            parent[px] = py;
        } else if(rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        
        return true;
    }
};

int kruskalMST(int n, vector<tuple<int, int, int>>& edges) {
    // edges: {weight, u, v}
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    int mstWeight = 0;
    int edgesUsed = 0;
    
    for(auto [weight, u, v] : edges) {
        if(dsu.unite(u, v)) {
            mstWeight += weight;
            edgesUsed++;
            if(edgesUsed == n - 1) break;
        }
    }
    
    return mstWeight;
}
```

**Time:** O(E log E)

---

### Day 52: More Graph Algorithms

#### 1. Bellman-Ford (Negative Weights)

```cpp
vector<int> bellmanFord(int n, vector<tuple<int, int, int>>& edges, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    
    // Relax all edges n-1 times
    for(int i = 0; i < n - 1; i++) {
        for(auto [u, v, weight] : edges) {
            if(dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Check for negative cycle
    for(auto [u, v, weight] : edges) {
        if(dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Negative cycle detected!" << endl;
            return {};
        }
    }
    
    return dist;
}
```

**Time:** O(VE)

---

#### 2. Floyd-Warshall (All Pairs Shortest Path)

```cpp
void floydWarshall(vector<vector<int>>& graph) {
    int n = graph.size();
    
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(graph[i][k] != INT_MAX && graph[k][j] != INT_MAX) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }
}
```

**Time:** O(V³)

---

## Day 53-54: Dynamic Programming Basics

### Day 53: DP Introduction

#### What is DP?
- Optimization technique
- Break problem into subproblems
- Store results (memoization/tabulation)
- Avoid recomputation

#### When to Use DP?
1. **Optimal Substructure:** Optimal solution contains optimal solutions to subproblems
2. **Overlapping Subproblems:** Same subproblems solved multiple times

---

#### 1. Fibonacci (Classic DP)

**Recursive (Exponential):**
```cpp
int fib(int n) {
    if(n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
// Time: O(2^n)
```

**Memoization (Top-Down):**
```cpp
int fibMemo(int n, vector<int>& dp) {
    if(n <= 1) return n;
    
    if(dp[n] != -1) return dp[n];
    
    dp[n] = fibMemo(n-1, dp) + fibMemo(n-2, dp);
    return dp[n];
}

int fib(int n) {
    vector<int> dp(n+1, -1);
    return fibMemo(n, dp);
}
// Time: O(n), Space: O(n)
```

**Tabulation (Bottom-Up):**
```cpp
int fib(int n) {
    if(n <= 1) return n;
    
    vector<int> dp(n+1);
    dp[0] = 0;
    dp[1] = 1;
    
    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}
// Time: O(n), Space: O(n)
```

**Space Optimized:**
```cpp
int fib(int n) {
    if(n <= 1) return n;
    
    int prev2 = 0, prev1 = 1;
    
    for(int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}
// Time: O(n), Space: O(1)
```

---

#### 2. Climbing Stairs

```cpp
int climbStairs(int n) {
    if(n <= 2) return n;
    
    vector<int> dp(n+1);
    dp[1] = 1;
    dp[2] = 2;
    
    for(int i = 3; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}
```

---

#### 3. House Robber

```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];
    
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    
    for(int i = 2; i < n; i++) {
        dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
    }
    
    return dp[n-1];
}
```

---

#### 4. Min Cost Climbing Stairs

```cpp
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n+1);
    
    for(int i = 2; i <= n; i++) {
        dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
    }
    
    return dp[n];
}
```

---

### Day 54: Classic DP Problems

#### 1. 0/1 Knapsack

```cpp
int knapsack(vector<int>& weights, vector<int>& values, int W) {
    int n = weights.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
    
    for(int i = 1; i <= n; i++) {
        for(int w = 1; w <= W; w++) {
            if(weights[i-1] <= w) {
                dp[i][w] = max(dp[i-1][w], 
                              values[i-1] + dp[i-1][w - weights[i-1]]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    return dp[n][W];
}
```

**Time:** O(nW), **Space:** O(nW)

---

#### 2. Longest Common Subsequence (LCS)

```cpp
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(text1[i-1] == text2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[m][n];
}
```

---

#### 3. Longest Increasing Subsequence (LIS)

```cpp
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    int maxLen = 1;
    
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLen = max(maxLen, dp[i]);
    }
    
    return maxLen;
}
```

**Time:** O(n²)

---

#### 4. Coin Change

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    
    for(int i = 1; i <= amount; i++) {
        for(int coin : coins) {
            if(i >= coin && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}
```

---

## Day 55-56: Greedy & Backtracking

### Day 55: Greedy Algorithms

#### Concept
- Make locally optimal choice at each step
- Hope to find global optimum
- Doesn't always work (need proof)

---

#### 1. Activity Selection

```cpp
int activitySelection(vector<pair<int, int>>& activities) {
    // {end_time, start_time}
    sort(activities.begin(), activities.end());
    
    int count = 1;
    int lastEnd = activities[0].first;
    
    for(int i = 1; i < activities.size(); i++) {
        if(activities[i].second >= lastEnd) {
            count++;
            lastEnd = activities[i].first;
        }
    }
    
    return count;
}
```

---

#### 2. Fractional Knapsack

```cpp
double fractionalKnapsack(vector<pair<int, int>>& items, int W) {
    // {value, weight}
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
        double r1 = (double)a.first / a.second;
        double r2 = (double)b.first / b.second;
        return r1 > r2;
    });
    
    double totalValue = 0;
    
    for(auto [value, weight] : items) {
        if(W >= weight) {
            totalValue += value;
            W -= weight;
        } else {
            totalValue += value * ((double)W / weight);
            break;
        }
    }
    
    return totalValue;
}
```

---

#### 3. Minimum Platforms

```cpp
int minPlatforms(vector<int>& arrivals, vector<int>& departures) {
    sort(arrivals.begin(), arrivals.end());
    sort(departures.begin(), departures.end());
    
    int platforms = 0, maxPlatforms = 0;
    int i = 0, j = 0;
    int n = arrivals.size();
    
    while(i < n && j < n) {
        if(arrivals[i] <= departures[j]) {
            platforms++;
            maxPlatforms = max(maxPlatforms, platforms);
            i++;
        } else {
            platforms--;
            j++;
        }
    }
    
    return maxPlatforms;
}
```

---

### Day 56: Backtracking

#### Concept
- Try all possibilities
- Backtrack when solution not possible
- Prune search space

---

#### 1. N-Queens Problem

```cpp
bool isSafe(vector<string>& board, int row, int col, int n) {
    // Check column
    for(int i = 0; i < row; i++) {
        if(board[i][col] == 'Q') return false;
    }
    
    // Check upper left diagonal
    for(int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if(board[i][j] == 'Q') return false;
    }
    
    // Check upper right diagonal
    for(int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if(board[i][j] == 'Q') return false;
    }
    
    return true;
}

void solveNQueens(int row, int n, vector<string>& board, 
                  vector<vector<string>>& result) {
    if(row == n) {
        result.push_back(board);
        return;
    }
    
    for(int col = 0; col < n; col++) {
        if(isSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            solveNQueens(row + 1, n, board, result);
            board[row][col] = '.';  // Backtrack
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    solveNQueens(0, n, board, result);
    return result;
}
```

---

#### 2. Sudoku Solver

```cpp
bool isValid(vector<vector<char>>& board, int row, int col, char num) {
    for(int i = 0; i < 9; i++) {
        if(board[row][i] == num) return false;
        if(board[i][col] == num) return false;
        if(board[3*(row/3) + i/3][3*(col/3) + i%3] == num) return false;
    }
    return true;
}

bool solveSudoku(vector<vector<char>>& board) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(board[i][j] == '.') {
                for(char num = '1'; num <= '9'; num++) {
                    if(isValid(board, i, j, num)) {
                        board[i][j] = num;
                        
                        if(solveSudoku(board)) {
                            return true;
                        }
                        
                        board[i][j] = '.';  // Backtrack
                    }
                }
                return false;
            }
        }
    }
    return true;
}
```

---

## Day 57-58: Tries & Disjoint Set

### Day 57: Tries

#### Trie Node Structure

```cpp
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    
    TrieNode() {
        for(int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* curr = root;
        
        for(char c : word) {
            int index = c - 'a';
            if(curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index];
        }
        
        curr->isEndOfWord = true;
    }
    
    bool search(string word) {
        TrieNode* curr = root;
        
        for(char c : word) {
            int index = c - 'a';
            if(curr->children[index] == nullptr) {
                return false;
            }
            curr = curr->children[index];
        }
        
        return curr->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        
        for(char c : prefix) {
            int index = c - 'a';
            if(curr->children[index] == nullptr) {
                return false;
            }
            curr = curr->children[index];
        }
        
        return true;
    }
};
```

---

### Day 58: Disjoint Set Union (DSU)

```cpp
class DSU {
private:
    vector<int> parent, rank, size;
    
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1);
        
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if(px == py) return;
        
        // Union by rank
        if(rank[px] < rank[py]) {
            parent[px] = py;
            size[py] += size[px];
        } else if(rank[px] > rank[py]) {
            parent[py] = px;
            size[px] += size[py];
        } else {
            parent[py] = px;
            size[px] += size[py];
            rank[px]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    
    int getSize(int x) {
        return size[find(x)];
    }
};
```

**Applications:**
- Kruskal's MST
- Cycle detection
- Connected components
- Network connectivity

---

## Day 59-60: Final Revision & Mock Tests

### Revision Checklist

#### Week 1: Arrays & Math ✓
- [ ] Array operations
- [ ] Two pointers
- [ ] Sliding window
- [ ] Bit manipulation
- [ ] Prime numbers
- [ ] Complexity analysis

#### Week 2: Recursion & Searching ✓
- [ ] Recursion patterns
- [ ] Binary search
- [ ] Binary search variants

#### Week 3: Sorting ✓
- [ ] All sorting algorithms
- [ ] Time complexities
- [ ] When to use which

#### Week 4: Linked Lists ✓
- [ ] Singly, doubly, circular
- [ ] Reverse linked list
- [ ] Detect cycle
- [ ] Fast-slow pointers

#### Week 5: Stack & Queue ✓
- [ ] Stack operations
- [ ] Queue operations
- [ ] Monotonic stack
- [ ] BFS using queue

#### Week 6: Trees ✓
- [ ] Tree traversals (all 4)
- [ ] BST operations
- [ ] LCA, diameter, balanced

#### Week 7: Heaps, Graphs, Hashing ✓
- [ ] Heap operations
- [ ] BFS and DFS
- [ ] Cycle detection
- [ ] Topological sort
- [ ] Hash map operations

#### Week 8: Advanced ✓
- [ ] Dijkstra's algorithm
- [ ] MST (Prim's, Kruskal's)
- [ ] Basic DP patterns
- [ ] Greedy approach
- [ ] Backtracking

---

### Mock Test Problems (30 problems)

#### Easy (10)
1. Two sum
2. Valid parentheses
3. Merge two sorted lists
4. Maximum subarray (Kadane's)
5. Binary search
6. Reverse linked list
7. Inorder traversal
8. Level order traversal
9. First non-repeating character
10. Climbing stairs

#### Medium (15)
11. Three sum
12. Container with most water
13. Longest substring without repeating
14. Group anagrams
15. Kth largest element
16. Top k frequent elements
17. Number of islands
18. Course schedule
19. LCA in binary tree
20. Validate BST
21. Kth smallest in BST
22. Word search
23. Combination sum
24. Permutations
25. Subsets

#### Hard (5)
26. Trapping rain water
27. Merge k sorted lists
28. Longest consecutive sequence
29. Word ladder
30. Serialize and deserialize binary tree

---

## Algorithm Complexity Cheat Sheet

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) |
| Binary Search | O(1) | O(log n) | O(log n) | O(1) |
| BFS | O(V+E) | O(V+E) | O(V+E) | O(V) |
| DFS | O(V+E) | O(V+E) | O(V+E) | O(V) |
| Dijkstra | - | O((V+E) log V) | O((V+E) log V) | O(V) |

---

## Final Tips for Success

### Before Interview/Contest
1. Revise all major algorithms
2. Practice on whiteboard
3. Time yourself
4. Review weak areas

### During Problem Solving
1. Read problem carefully
2. Think before coding
3. Consider edge cases
4. Test with examples
5. Analyze complexity

### After 2 Months
- Continue solving daily (3-5 problems)
- Participate in contests
- Learn advanced topics (Segment Tree, Fenwick Tree, etc.)
- Practice system design

---

## Congratulations! 🎉

You've completed the 2-month DSA plan! You now have:
- Strong foundation in all major data structures
- Understanding of algorithm design techniques
- Problem-solving skills
- 200+ problems solved

**Keep practicing and good luck with your interviews!**

---

## What's Next?

### Continue Learning
- Advanced DP (Bitmask DP, DP on trees)
- Advanced Graph (Network flow, Strongly connected components)
- Segment Trees & Fenwick Trees
- String algorithms (KMP, Rabin-Karp, Z-algorithm)
- Advanced data structures (Trie variations, Suffix arrays)

### Practice Platforms
- LeetCode (continue daily)
- Codeforces (contests)
- AtCoder (quality problems)
- HackerRank (interview prep)

### Mock Interviews
- Pramp
- Interviewing.io
- LeetCode mock interviews
- Practice with friends

**Remember:** DSA is a journey, not a destination. Keep learning and practicing!
