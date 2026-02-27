# Week 6: Trees & Binary Search Trees

## Overview
Master tree data structures, traversal techniques, and binary search trees.

---

## Day 36-38: Binary Trees

### Day 36: Tree Basics

#### Terminology

**Tree:** Hierarchical data structure with nodes connected by edges

**Key Terms:**
- **Root:** Top node (no parent)
- **Parent:** Node with children
- **Child:** Node connected to parent
- **Leaf:** Node with no children
- **Sibling:** Nodes with same parent
- **Ancestor:** Parent, grandparent, etc.
- **Descendant:** Child, grandchild, etc.
- **Depth:** Distance from root
- **Height:** Distance to farthest leaf
- **Level:** Depth + 1

#### Node Structure

```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
```

---

#### Types of Binary Trees

**1. Full Binary Tree**
- Every node has 0 or 2 children

**2. Complete Binary Tree**
- All levels filled except possibly last
- Last level filled from left

**3. Perfect Binary Tree**
- All internal nodes have 2 children
- All leaves at same level

**4. Balanced Binary Tree**
- Height difference of left and right subtrees ≤ 1

**5. Degenerate Tree**
- Every node has only one child (like linked list)

---

#### Basic Operations

##### 1. Create Tree
```cpp
TreeNode* createTree() {
    int data;
    cin >> data;
    
    if(data == -1) return nullptr;
    
    TreeNode* root = new TreeNode(data);
    root->left = createTree();
    root->right = createTree();
    
    return root;
}
```

##### 2. Height of Tree
```cpp
int height(TreeNode* root) {
    if(root == nullptr) return 0;
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return 1 + max(leftHeight, rightHeight);
}
```

##### 3. Count Nodes
```cpp
int countNodes(TreeNode* root) {
    if(root == nullptr) return 0;
    
    return 1 + countNodes(root->left) + countNodes(root->right);
}
```

##### 4. Count Leaf Nodes
```cpp
int countLeaves(TreeNode* root) {
    if(root == nullptr) return 0;
    if(root->left == nullptr && root->right == nullptr) return 1;
    
    return countLeaves(root->left) + countLeaves(root->right);
}
```

---

### Day 37: Tree Traversals (DFS)

#### 1. Inorder Traversal (Left → Root → Right)

**Recursive:**
```cpp
void inorder(TreeNode* root) {
    if(root == nullptr) return;
    
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
```

**Iterative:**
```cpp
void inorderIterative(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;
    
    while(curr != nullptr || !st.empty()) {
        while(curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }
        
        curr = st.top();
        st.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}
```

---

#### 2. Preorder Traversal (Root → Left → Right)

**Recursive:**
```cpp
void preorder(TreeNode* root) {
    if(root == nullptr) return;
    
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
```

**Iterative:**
```cpp
void preorderIterative(TreeNode* root) {
    if(root == nullptr) return;
    
    stack<TreeNode*> st;
    st.push(root);
    
    while(!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();
        cout << curr->data << " ";
        
        if(curr->right) st.push(curr->right);
        if(curr->left) st.push(curr->left);
    }
}
```

---

#### 3. Postorder Traversal (Left → Right → Root)

**Recursive:**
```cpp
void postorder(TreeNode* root) {
    if(root == nullptr) return;
    
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}
```

**Iterative:**
```cpp
void postorderIterative(TreeNode* root) {
    if(root == nullptr) return;
    
    stack<TreeNode*> st1, st2;
    st1.push(root);
    
    while(!st1.empty()) {
        TreeNode* curr = st1.top();
        st1.pop();
        st2.push(curr);
        
        if(curr->left) st1.push(curr->left);
        if(curr->right) st1.push(curr->right);
    }
    
    while(!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}
```

---

### Day 38: Level Order Traversal (BFS)

#### 1. Level Order (BFS)

```cpp
void levelOrder(TreeNode* root) {
    if(root == nullptr) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while(!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        cout << curr->data << " ";
        
        if(curr->left) q.push(curr->left);
        if(curr->right) q.push(curr->right);
    }
}
```

---

#### 2. Level Order (Line by Line)

```cpp
void levelOrderLineByLine(TreeNode* root) {
    if(root == nullptr) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while(!q.empty()) {
        int size = q.size();
        
        for(int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            cout << curr->data << " ";
            
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }
        cout << endl;
    }
}
```

---

#### 3. Zigzag Level Order

```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if(root == nullptr) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    
    while(!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        
        for(int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            int index = leftToRight ? i : size - 1 - i;
            level[index] = curr->data;
            
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }
        
        leftToRight = !leftToRight;
        result.push_back(level);
    }
    
    return result;
}
```

---

#### 4. Vertical Order Traversal

```cpp
vector<vector<int>> verticalOrder(TreeNode* root) {
    vector<vector<int>> result;
    if(root == nullptr) return result;
    
    map<int, vector<int>> m;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
    while(!q.empty()) {
        auto [node, col] = q.front();
        q.pop();
        
        m[col].push_back(node->data);
        
        if(node->left) q.push({node->left, col - 1});
        if(node->right) q.push({node->right, col + 1});
    }
    
    for(auto& [col, nodes] : m) {
        result.push_back(nodes);
    }
    
    return result;
}
```

---

## Day 39-42: Binary Search Tree (BST)

### Day 39: BST Basics

#### BST Property
- Left subtree < Root < Right subtree
- This property holds for every node

#### Node Structure (Same as Binary Tree)
```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
```

---

#### 1. Search in BST

**Recursive:**
```cpp
TreeNode* search(TreeNode* root, int key) {
    if(root == nullptr || root->data == key) {
        return root;
    }
    
    if(key < root->data) {
        return search(root->left, key);
    }
    
    return search(root->right, key);
}
```

**Iterative:**
```cpp
TreeNode* searchIterative(TreeNode* root, int key) {
    while(root != nullptr && root->data != key) {
        if(key < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}
```

**Time:** O(h) where h is height  
**Space:** O(1) iterative, O(h) recursive

---

#### 2. Insert in BST

```cpp
TreeNode* insert(TreeNode* root, int key) {
    if(root == nullptr) {
        return new TreeNode(key);
    }
    
    if(key < root->data) {
        root->left = insert(root->left, key);
    } else if(key > root->data) {
        root->right = insert(root->right, key);
    }
    
    return root;
}
```

**Time:** O(h)  
**Space:** O(h)

---

#### 3. Find Minimum and Maximum

```cpp
TreeNode* findMin(TreeNode* root) {
    if(root == nullptr) return nullptr;
    
    while(root->left != nullptr) {
        root = root->left;
    }
    return root;
}

TreeNode* findMax(TreeNode* root) {
    if(root == nullptr) return nullptr;
    
    while(root->right != nullptr) {
        root = root->right;
    }
    return root;
}
```

**Time:** O(h)

---

### Day 40: BST Deletion

#### Delete Node in BST

```cpp
TreeNode* deleteNode(TreeNode* root, int key) {
    if(root == nullptr) return nullptr;
    
    if(key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // Node found
        
        // Case 1: Leaf node
        if(root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        
        // Case 2: One child
        if(root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        if(root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        
        // Case 3: Two children
        TreeNode* minRight = findMin(root->right);
        root->data = minRight->data;
        root->right = deleteNode(root->right, minRight->data);
    }
    
    return root;
}
```

**Time:** O(h)  
**Space:** O(h)

---

#### Validate BST

```cpp
bool isValidBST(TreeNode* root, long minVal, long maxVal) {
    if(root == nullptr) return true;
    
    if(root->data <= minVal || root->data >= maxVal) {
        return false;
    }
    
    return isValidBST(root->left, minVal, root->data) &&
           isValidBST(root->right, root->data, maxVal);
}

bool isValidBST(TreeNode* root) {
    return isValidBST(root, LONG_MIN, LONG_MAX);
}
```

**Time:** O(n)  
**Space:** O(h)

---

### Day 41: BST Advanced Operations

#### 1. Kth Smallest Element

```cpp
void inorder(TreeNode* root, int& k, int& result) {
    if(root == nullptr) return;
    
    inorder(root->left, k, result);
    
    k--;
    if(k == 0) {
        result = root->data;
        return;
    }
    
    inorder(root->right, k, result);
}

int kthSmallest(TreeNode* root, int k) {
    int result = -1;
    inorder(root, k, result);
    return result;
}
```

---

#### 2. Kth Largest Element

```cpp
void reverseInorder(TreeNode* root, int& k, int& result) {
    if(root == nullptr) return;
    
    reverseInorder(root->right, k, result);
    
    k--;
    if(k == 0) {
        result = root->data;
        return;
    }
    
    reverseInorder(root->left, k, result);
}

int kthLargest(TreeNode* root, int k) {
    int result = -1;
    reverseInorder(root, k, result);
    return result;
}
```

---

#### 3. Lowest Common Ancestor (LCA)

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr) return nullptr;
    
    // If both nodes are smaller, LCA is in left subtree
    if(p->data < root->data && q->data < root->data) {
        return lowestCommonAncestor(root->left, p, q);
    }
    
    // If both nodes are larger, LCA is in right subtree
    if(p->data > root->data && q->data > root->data) {
        return lowestCommonAncestor(root->right, p, q);
    }
    
    // Otherwise, root is LCA
    return root;
}
```

---

#### 4. Inorder Successor

```cpp
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* successor = nullptr;
    
    while(root != nullptr) {
        if(p->data < root->data) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    return successor;
}
```

---

#### 5. Inorder Predecessor

```cpp
TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
    TreeNode* predecessor = nullptr;
    
    while(root != nullptr) {
        if(p->data > root->data) {
            predecessor = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    
    return predecessor;
}
```

---

### Day 42: BST Construction & Conversion

#### 1. Convert Sorted Array to BST

```cpp
TreeNode* sortedArrayToBST(vector<int>& nums, int left, int right) {
    if(left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    
    root->left = sortedArrayToBST(nums, left, mid - 1);
    root->right = sortedArrayToBST(nums, mid + 1, right);
    
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return sortedArrayToBST(nums, 0, nums.size() - 1);
}
```

---

#### 2. BST to Sorted Array (Inorder)

```cpp
void bstToArray(TreeNode* root, vector<int>& arr) {
    if(root == nullptr) return;
    
    bstToArray(root->left, arr);
    arr.push_back(root->data);
    bstToArray(root->right, arr);
}
```

---

#### 3. Merge Two BSTs

```cpp
TreeNode* mergeBSTs(TreeNode* root1, TreeNode* root2) {
    vector<int> arr1, arr2;
    
    bstToArray(root1, arr1);
    bstToArray(root2, arr2);
    
    // Merge two sorted arrays
    vector<int> merged;
    int i = 0, j = 0;
    
    while(i < arr1.size() && j < arr2.size()) {
        if(arr1[i] < arr2[j]) {
            merged.push_back(arr1[i++]);
        } else {
            merged.push_back(arr2[j++]);
        }
    }
    
    while(i < arr1.size()) merged.push_back(arr1[i++]);
    while(j < arr2.size()) merged.push_back(arr2[j++]);
    
    return sortedArrayToBST(merged);
}
```

---

## Common Tree Problems

### 1. Diameter of Binary Tree

```cpp
int diameterHelper(TreeNode* root, int& diameter) {
    if(root == nullptr) return 0;
    
    int leftHeight = diameterHelper(root->left, diameter);
    int rightHeight = diameterHelper(root->right, diameter);
    
    diameter = max(diameter, leftHeight + rightHeight);
    
    return 1 + max(leftHeight, rightHeight);
}

int diameter(TreeNode* root) {
    int diameter = 0;
    diameterHelper(root, diameter);
    return diameter;
}
```

---

### 2. Check if Balanced

```cpp
int checkHeight(TreeNode* root) {
    if(root == nullptr) return 0;
    
    int leftHeight = checkHeight(root->left);
    if(leftHeight == -1) return -1;
    
    int rightHeight = checkHeight(root->right);
    if(rightHeight == -1) return -1;
    
    if(abs(leftHeight - rightHeight) > 1) return -1;
    
    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(TreeNode* root) {
    return checkHeight(root) != -1;
}
```

---

### 3. Maximum Path Sum

```cpp
int maxPathSumHelper(TreeNode* root, int& maxSum) {
    if(root == nullptr) return 0;
    
    int left = max(0, maxPathSumHelper(root->left, maxSum));
    int right = max(0, maxPathSumHelper(root->right, maxSum));
    
    maxSum = max(maxSum, left + right + root->data);
    
    return root->data + max(left, right);
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumHelper(root, maxSum);
    return maxSum;
}
```

---

## Practice Problems (Week 6)

### Binary Trees (15 problems)

#### Day 36: Basics (3)
1. Height of binary tree
2. Count nodes in binary tree
3. Count leaf nodes

#### Day 37: Traversals (4)
4. Inorder traversal (recursive & iterative)
5. Preorder traversal (recursive & iterative)
6. Postorder traversal (recursive & iterative)
7. All three traversals in one function

#### Day 38: Level Order (4)
8. Level order traversal
9. Level order line by line
10. Zigzag level order
11. Vertical order traversal

#### Mixed (4)
12. Diameter of binary tree
13. Check if balanced
14. Maximum path sum
15. Lowest common ancestor

---

### BST (15 problems)

#### Day 39: Basics (4)
16. Search in BST
17. Insert in BST
18. Find min and max in BST
19. Validate BST

#### Day 40: Deletion (3)
20. Delete node in BST
21. Trim BST
22. Delete nodes in range

#### Day 41: Advanced (4)
23. Kth smallest in BST
24. Kth largest in BST
25. LCA in BST
26. Inorder successor/predecessor

#### Day 42: Construction (4)
27. Convert sorted array to BST
28. Convert BST to sorted array
29. Merge two BSTs
30. Recover BST (two nodes swapped)

---

## Time Complexity Summary

| Operation | Binary Tree | BST (Balanced) | BST (Skewed) |
|-----------|-------------|----------------|--------------|
| Search | O(n) | O(log n) | O(n) |
| Insert | O(n) | O(log n) | O(n) |
| Delete | O(n) | O(log n) | O(n) |
| Traversal | O(n) | O(n) | O(n) |

---

## Week 6 Checklist

- [ ] Understand tree terminology
- [ ] Implement all three DFS traversals
- [ ] Implement BFS (level order)
- [ ] Master BST operations
- [ ] Understand BST property
- [ ] Solve diameter and balanced problems
- [ ] Implement BST construction
- [ ] Solve 30 tree problems

---

## Tips

1. **Draw trees** - Always visualize
2. **Recursion** - Most tree problems use recursion
3. **Base case** - nullptr check
4. **BST property** - Left < Root < Right
5. **Inorder of BST** - Always sorted
6. **Use queue for BFS** - Level order
7. **Use stack for DFS** - Iterative traversal

---

**Next Week:** Heaps, Graphs & Hashing!
