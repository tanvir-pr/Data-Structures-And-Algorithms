# Week 5: Stack & Queue

## Overview
Master LIFO (Stack) and FIFO (Queue) data structures, their implementations, and applications.

---

## Day 29-31: Stack

### Day 29: Stack Basics & Array Implementation

#### Concept
- **LIFO:** Last In First Out
- Think of a stack of plates
- Operations only at one end (top)

#### Operations
- **Push:** Add element to top - O(1)
- **Pop:** Remove element from top - O(1)
- **Peek/Top:** View top element - O(1)
- **isEmpty:** Check if empty - O(1)
- **Size:** Get number of elements - O(1)

---

#### Implementation Using Array

```cpp
#define MAX 1000

class Stack {
private:
    int arr[MAX];
    int top;
    
public:
    Stack() {
        top = -1;
    }
    
    bool push(int x) {
        if(top >= MAX - 1) {
            cout << "Stack Overflow" << endl;
            return false;
        }
        arr[++top] = x;
        return true;
    }
    
    int pop() {
        if(top < 0) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return arr[top--];
    }
    
    int peek() {
        if(top < 0) {
            cout << "Stack is Empty" << endl;
            return -1;
        }
        return arr[top];
    }
    
    bool isEmpty() {
        return (top < 0);
    }
    
    int size() {
        return top + 1;
    }
};
```

**Pros:** Fast, simple  
**Cons:** Fixed size

---

### Day 30: Stack Using Linked List

#### Implementation

```cpp
struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class Stack {
private:
    Node* top;
    int count;
    
public:
    Stack() {
        top = nullptr;
        count = 0;
    }
    
    void push(int x) {
        Node* newNode = new Node(x);
        newNode->next = top;
        top = newNode;
        count++;
    }
    
    int pop() {
        if(isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        Node* temp = top;
        int popped = top->data;
        top = top->next;
        delete temp;
        count--;
        return popped;
    }
    
    int peek() {
        if(isEmpty()) {
            cout << "Stack is Empty" << endl;
            return -1;
        }
        return top->data;
    }
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    int size() {
        return count;
    }
};
```

**Pros:** Dynamic size  
**Cons:** Extra memory for pointers

---

#### Using C++ STL Stack

```cpp
#include <stack>

stack<int> s;

s.push(10);          // Push element
s.pop();             // Pop element
s.top();             // Get top element
s.empty();           // Check if empty
s.size();            // Get size
```

---

### Day 31: Stack Applications

#### 1. Valid Parentheses

```cpp
bool isValid(string s) {
    stack<char> st;
    
    for(char c : s) {
        if(c == '(' || c == '{' || c == '[') {
            st.push(c);
        }
        else {
            if(st.empty()) return false;
            
            char top = st.top();
            if((c == ')' && top == '(') ||
               (c == '}' && top == '{') ||
               (c == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    
    return st.empty();
}
```

---

#### 2. Next Greater Element

```cpp
vector<int> nextGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;
    
    for(int i = n-1; i >= 0; i--) {
        while(!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }
        
        if(!st.empty()) {
            result[i] = st.top();
        }
        
        st.push(arr[i]);
    }
    
    return result;
}
```

---

#### 3. Evaluate Postfix Expression

```cpp
int evaluatePostfix(string exp) {
    stack<int> st;
    
    for(char c : exp) {
        if(isdigit(c)) {
            st.push(c - '0');
        }
        else {
            int val2 = st.top(); st.pop();
            int val1 = st.top(); st.pop();
            
            switch(c) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
            }
        }
    }
    
    return st.top();
}
```

---

#### 4. Infix to Postfix Conversion

```cpp
int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    if(op == '^') return 3;
    return 0;
}

string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";
    
    for(char c : infix) {
        if(isalnum(c)) {
            postfix += c;
        }
        else if(c == '(') {
            st.push(c);
        }
        else if(c == ')') {
            while(!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();  // Remove '('
        }
        else {  // Operator
            while(!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    
    while(!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    
    return postfix;
}
```

---

#### 5. Stock Span Problem

```cpp
vector<int> calculateSpan(vector<int>& price) {
    int n = price.size();
    vector<int> span(n);
    stack<int> st;
    
    for(int i = 0; i < n; i++) {
        while(!st.empty() && price[st.top()] <= price[i]) {
            st.pop();
        }
        
        span[i] = st.empty() ? (i + 1) : (i - st.top());
        st.push(i);
    }
    
    return span;
}
```

---

#### 6. Largest Rectangle in Histogram

```cpp
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;
    int n = heights.size();
    
    for(int i = 0; i < n; i++) {
        while(!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    
    while(!st.empty()) {
        int h = heights[st.top()];
        st.pop();
        int width = st.empty() ? n : n - st.top() - 1;
        maxArea = max(maxArea, h * width);
    }
    
    return maxArea;
}
```

---

## Day 32-35: Queue

### Day 32: Queue Basics & Array Implementation

#### Concept
- **FIFO:** First In First Out
- Think of a line at ticket counter
- Operations at both ends (front and rear)

#### Operations
- **Enqueue:** Add element at rear - O(1)
- **Dequeue:** Remove element from front - O(1)
- **Front:** View front element - O(1)
- **isEmpty:** Check if empty - O(1)
- **Size:** Get number of elements - O(1)

---

#### Simple Array Implementation

```cpp
#define MAX 1000

class Queue {
private:
    int arr[MAX];
    int front, rear;
    int count;
    
public:
    Queue() {
        front = 0;
        rear = -1;
        count = 0;
    }
    
    bool enqueue(int x) {
        if(count >= MAX) {
            cout << "Queue Overflow" << endl;
            return false;
        }
        rear = (rear + 1) % MAX;
        arr[rear] = x;
        count++;
        return true;
    }
    
    int dequeue() {
        if(isEmpty()) {
            cout << "Queue Underflow" << endl;
            return -1;
        }
        int item = arr[front];
        front = (front + 1) % MAX;
        count--;
        return item;
    }
    
    int getFront() {
        if(isEmpty()) {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        return arr[front];
    }
    
    int getRear() {
        if(isEmpty()) {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        return arr[rear];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    int size() {
        return count;
    }
};
```

---

### Day 33: Queue Using Linked List

#### Implementation

```cpp
struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;
    int count;
    
public:
    Queue() {
        front = rear = nullptr;
        count = 0;
    }
    
    void enqueue(int x) {
        Node* newNode = new Node(x);
        
        if(rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }
    
    int dequeue() {
        if(isEmpty()) {
            cout << "Queue Underflow" << endl;
            return -1;
        }
        
        Node* temp = front;
        int item = front->data;
        front = front->next;
        
        if(front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
        count--;
        return item;
    }
    
    int getFront() {
        if(isEmpty()) {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        return front->data;
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    int size() {
        return count;
    }
};
```

---

#### Using C++ STL Queue

```cpp
#include <queue>

queue<int> q;

q.push(10);          // Enqueue
q.pop();             // Dequeue
q.front();           // Get front element
q.back();            // Get rear element
q.empty();           // Check if empty
q.size();            // Get size
```

---

### Day 34: Special Queues

#### 1. Circular Queue

```cpp
class CircularQueue {
private:
    int* arr;
    int front, rear;
    int capacity;
    int count;
    
public:
    CircularQueue(int size) {
        arr = new int[size];
        capacity = size;
        front = 0;
        rear = -1;
        count = 0;
    }
    
    bool enqueue(int x) {
        if(isFull()) {
            return false;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = x;
        count++;
        return true;
    }
    
    int dequeue() {
        if(isEmpty()) {
            return -1;
        }
        int item = arr[front];
        front = (front + 1) % capacity;
        count--;
        return item;
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
    
    int getFront() {
        if(isEmpty()) return -1;
        return arr[front];
    }
};
```

---

#### 2. Priority Queue (Using STL)

```cpp
#include <queue>

// Max heap (default)
priority_queue<int> maxHeap;

// Min heap
priority_queue<int, vector<int>, greater<int>> minHeap;

maxHeap.push(10);
maxHeap.pop();
maxHeap.top();
maxHeap.empty();
maxHeap.size();
```

---

#### 3. Deque (Double-Ended Queue)

```cpp
#include <deque>

deque<int> dq;

dq.push_back(10);    // Add at rear
dq.push_front(20);   // Add at front
dq.pop_back();       // Remove from rear
dq.pop_front();      // Remove from front
dq.front();          // Get front
dq.back();           // Get rear
dq.empty();
dq.size();
```

---

### Day 35: Queue Applications

#### 1. Implement Stack Using Queue

```cpp
class MyStack {
private:
    queue<int> q1, q2;
    
public:
    void push(int x) {
        q2.push(x);
        
        while(!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        swap(q1, q2);
    }
    
    int pop() {
        if(q1.empty()) return -1;
        int top = q1.front();
        q1.pop();
        return top;
    }
    
    int top() {
        if(q1.empty()) return -1;
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};
```

---

#### 2. Implement Queue Using Stack

```cpp
class MyQueue {
private:
    stack<int> s1, s2;
    
public:
    void enqueue(int x) {
        s1.push(x);
    }
    
    int dequeue() {
        if(s2.empty()) {
            while(!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        
        if(s2.empty()) return -1;
        
        int front = s2.top();
        s2.pop();
        return front;
    }
    
    int front() {
        if(s2.empty()) {
            while(!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        
        if(s2.empty()) return -1;
        return s2.top();
    }
    
    bool empty() {
        return s1.empty() && s2.empty();
    }
};
```

---

#### 3. First Non-Repeating Character in Stream

```cpp
void firstNonRepeating(string stream) {
    queue<char> q;
    unordered_map<char, int> freq;
    
    for(char c : stream) {
        freq[c]++;
        q.push(c);
        
        while(!q.empty() && freq[q.front()] > 1) {
            q.pop();
        }
        
        if(q.empty()) {
            cout << "-1 ";
        } else {
            cout << q.front() << " ";
        }
    }
}
```

---

#### 4. Generate Binary Numbers from 1 to N

```cpp
vector<string> generateBinary(int n) {
    vector<string> result;
    queue<string> q;
    
    q.push("1");
    
    for(int i = 0; i < n; i++) {
        string curr = q.front();
        q.pop();
        result.push_back(curr);
        
        q.push(curr + "0");
        q.push(curr + "1");
    }
    
    return result;
}
```

---

#### 5. Sliding Window Maximum

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    
    for(int i = 0; i < nums.size(); i++) {
        // Remove elements outside window
        if(!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements
        while(!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if(i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}
```

---

#### 6. Rotten Oranges (BFS)

```cpp
int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0;
    
    // Add all rotten oranges to queue
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == 2) {
                q.push({i, j});
            } else if(grid[i][j] == 1) {
                fresh++;
            }
        }
    }
    
    if(fresh == 0) return 0;
    
    int minutes = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while(!q.empty()) {
        int size = q.size();
        bool rotted = false;
        
        for(int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();
            
            for(int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                
                if(nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    q.push({nx, ny});
                    fresh--;
                    rotted = true;
                }
            }
        }
        
        if(rotted) minutes++;
    }
    
    return fresh == 0 ? minutes : -1;
}
```

---

## Stack vs Queue

| Feature | Stack | Queue |
|---------|-------|-------|
| Order | LIFO | FIFO |
| Operations | Push, Pop at same end | Enqueue at rear, Dequeue at front |
| Use Cases | Function calls, Undo, Backtracking | BFS, Scheduling, Buffering |
| Implementation | Array or Linked List | Array or Linked List |

---

## Practice Problems (Week 5)

### Stack (15 problems)

#### Day 29: Basics (4)
1. Implement stack using array
2. Implement stack using linked list
3. Implement min stack
4. Reverse string using stack

#### Day 30: Applications (4)
5. Valid parentheses
6. Next greater element
7. Next smaller element
8. Stock span problem

#### Day 31: Advanced (4)
9. Largest rectangle in histogram
10. Evaluate postfix expression
11. Infix to postfix conversion
12. Simplify path (Unix)

#### Mixed (3)
13. Celebrity problem
14. Remove k digits
15. Decode string

---

### Queue (13 problems)

#### Day 32: Basics (3)
16. Implement queue using array
17. Implement queue using linked list
18. Reverse queue

#### Day 33: Using Stacks (2)
19. Implement stack using queue
20. Implement queue using stack

#### Day 34: Special Queues (3)
21. Circular queue implementation
22. Design circular deque
23. First negative in window of size k

#### Day 35: Applications (5)
24. First non-repeating character in stream
25. Generate binary numbers 1 to n
26. Sliding window maximum
27. Rotten oranges (BFS)
28. Level order traversal (tree)

---

## Common Patterns

### Stack Patterns
1. **Monotonic Stack** - Next greater/smaller element
2. **Expression Evaluation** - Postfix, infix conversion
3. **Parenthesis Matching** - Valid brackets
4. **Backtracking** - DFS, undo operations

### Queue Patterns
1. **BFS** - Level order, shortest path
2. **Sliding Window** - Maximum in window
3. **Scheduling** - Task scheduling
4. **Stream Processing** - First non-repeating

---

## Week 5 Checklist

- [ ] Implement stack using array and linked list
- [ ] Implement queue using array and linked list
- [ ] Understand LIFO vs FIFO
- [ ] Master monotonic stack pattern
- [ ] Solve parenthesis problems
- [ ] Implement circular queue
- [ ] Understand deque operations
- [ ] Solve BFS problems using queue
- [ ] Solve 25-30 problems

---

## Tips

1. **Stack:** Think of function call stack, browser history
2. **Queue:** Think of printer queue, BFS traversal
3. **Draw diagrams:** Visualize push/pop operations
4. **Edge cases:** Empty, single element, full capacity
5. **STL:** Use STL for contests, implement for interviews

---

**Next Week:** Trees - Using stack (DFS) and queue (BFS) for traversal!
