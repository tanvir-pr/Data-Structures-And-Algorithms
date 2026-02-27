# Week 4: Linked Lists

## Overview
Master all types of linked lists - singly, doubly, and circular. Understand pointer manipulation and when to use linked lists over arrays.

---

## Day 22-24: Singly Linked List

### Day 22: Basics & Insertion

#### Concept
- Linear data structure
- Elements (nodes) connected via pointers
- Each node contains data and pointer to next node
- Dynamic size (no fixed size like arrays)

#### Node Structure
```cpp
struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};
```

#### Basic Operations

##### 1. Insert at Beginning
```cpp
Node* insertAtHead(Node* head, int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
    return head;
}
```
**Time:** O(1), **Space:** O(1)

##### 2. Insert at End
```cpp
Node* insertAtTail(Node* head, int data) {
    Node* newNode = new Node(data);
    
    if(head == nullptr) {
        return newNode;
    }
    
    Node* temp = head;
    while(temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}
```
**Time:** O(n), **Space:** O(1)

##### 3. Insert at Position
```cpp
Node* insertAtPosition(Node* head, int data, int pos) {
    if(pos == 0) {
        return insertAtHead(head, data);
    }
    
    Node* newNode = new Node(data);
    Node* temp = head;
    
    for(int i = 0; i < pos-1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    if(temp == nullptr) return head;
    
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}
```
**Time:** O(n), **Space:** O(1)

##### 4. Display/Traverse
```cpp
void display(Node* head) {
    Node* temp = head;
    while(temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
```
**Time:** O(n), **Space:** O(1)

---

### Day 23: Deletion & Searching

#### Deletion Operations

##### 1. Delete from Beginning
```cpp
Node* deleteFromHead(Node* head) {
    if(head == nullptr) return nullptr;
    
    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}
```
**Time:** O(1)

##### 2. Delete from End
```cpp
Node* deleteFromTail(Node* head) {
    if(head == nullptr || head->next == nullptr) {
        delete head;
        return nullptr;
    }
    
    Node* temp = head;
    while(temp->next->next != nullptr) {
        temp = temp->next;
    }
    
    delete temp->next;
    temp->next = nullptr;
    return head;
}
```
**Time:** O(n)

##### 3. Delete by Value
```cpp
Node* deleteByValue(Node* head, int val) {
    if(head == nullptr) return nullptr;
    
    if(head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    
    Node* temp = head;
    while(temp->next != nullptr && temp->next->data != val) {
        temp = temp->next;
    }
    
    if(temp->next == nullptr) return head;
    
    Node* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
    return head;
}
```
**Time:** O(n)

##### 4. Delete at Position
```cpp
Node* deleteAtPosition(Node* head, int pos) {
    if(head == nullptr) return nullptr;
    
    if(pos == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    
    Node* temp = head;
    for(int i = 0; i < pos-1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    if(temp == nullptr || temp->next == nullptr) return head;
    
    Node* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
    return head;
}
```
**Time:** O(n)

#### Searching Operations

##### 1. Search by Value
```cpp
bool search(Node* head, int val) {
    Node* temp = head;
    while(temp != nullptr) {
        if(temp->data == val) return true;
        temp = temp->next;
    }
    return false;
}
```
**Time:** O(n)

##### 2. Get Length
```cpp
int getLength(Node* head) {
    int count = 0;
    Node* temp = head;
    while(temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}
```
**Time:** O(n)

---

### Day 24: Advanced Operations

#### 1. Reverse Linked List (Iterative)
```cpp
Node* reverse(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    
    while(current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}
```
**Time:** O(n), **Space:** O(1)

#### 2. Reverse Linked List (Recursive)
```cpp
Node* reverseRecursive(Node* head) {
    if(head == nullptr || head->next == nullptr) {
        return head;
    }
    
    Node* newHead = reverseRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    
    return newHead;
}
```
**Time:** O(n), **Space:** O(n) - recursion stack

#### 3. Find Middle Element
```cpp
Node* findMiddle(Node* head) {
    if(head == nullptr) return nullptr;
    
    Node* slow = head;
    Node* fast = head;
    
    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}
```
**Time:** O(n), **Space:** O(1)

#### 4. Detect Cycle (Floyd's Algorithm)
```cpp
bool hasCycle(Node* head) {
    if(head == nullptr) return false;
    
    Node* slow = head;
    Node* fast = head;
    
    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if(slow == fast) return true;
    }
    
    return false;
}
```
**Time:** O(n), **Space:** O(1)

#### 5. Remove Nth Node from End
```cpp
Node* removeNthFromEnd(Node* head, int n) {
    Node* dummy = new Node(0);
    dummy->next = head;
    
    Node* first = dummy;
    Node* second = dummy;
    
    // Move first n+1 steps ahead
    for(int i = 0; i <= n; i++) {
        first = first->next;
    }
    
    // Move both until first reaches end
    while(first != nullptr) {
        first = first->next;
        second = second->next;
    }
    
    // Delete nth node from end
    Node* toDelete = second->next;
    second->next = second->next->next;
    delete toDelete;
    
    return dummy->next;
}
```
**Time:** O(n), **Space:** O(1)

#### 6. Merge Two Sorted Lists
```cpp
Node* mergeSortedLists(Node* l1, Node* l2) {
    Node* dummy = new Node(0);
    Node* current = dummy;
    
    while(l1 != nullptr && l2 != nullptr) {
        if(l1->data <= l2->data) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    
    if(l1 != nullptr) current->next = l1;
    if(l2 != nullptr) current->next = l2;
    
    return dummy->next;
}
```
**Time:** O(m+n), **Space:** O(1)

---

## Day 25-26: Doubly Linked List

### Day 25: DLL Basics

#### Node Structure
```cpp
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    
    DNode(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};
```

#### 1. Insert at Beginning
```cpp
DNode* insertAtHead(DNode* head, int data) {
    DNode* newNode = new DNode(data);
    
    if(head == nullptr) {
        return newNode;
    }
    
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    return head;
}
```

#### 2. Insert at End
```cpp
DNode* insertAtTail(DNode* head, int data) {
    DNode* newNode = new DNode(data);
    
    if(head == nullptr) {
        return newNode;
    }
    
    DNode* temp = head;
    while(temp->next != nullptr) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}
```

#### 3. Delete Node
```cpp
DNode* deleteNode(DNode* head, DNode* del) {
    if(head == nullptr || del == nullptr) return head;
    
    if(head == del) {
        head = del->next;
    }
    
    if(del->next != nullptr) {
        del->next->prev = del->prev;
    }
    
    if(del->prev != nullptr) {
        del->prev->next = del->next;
    }
    
    delete del;
    return head;
}
```

#### 4. Reverse DLL
```cpp
DNode* reverse(DNode* head) {
    DNode* temp = nullptr;
    DNode* current = head;
    
    while(current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    if(temp != nullptr) {
        head = temp->prev;
    }
    
    return head;
}
```

#### 5. Display Forward and Backward
```cpp
void displayForward(DNode* head) {
    DNode* temp = head;
    while(temp != nullptr) {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

void displayBackward(DNode* head) {
    if(head == nullptr) return;
    
    DNode* temp = head;
    while(temp->next != nullptr) {
        temp = temp->next;
    }
    
    while(temp != nullptr) {
        cout << temp->data << " <-> ";
        temp = temp->prev;
    }
    cout << "NULL" << endl;
}
```

---

### Day 26: DLL Advanced Problems

#### 1. Find Pairs with Given Sum
```cpp
void findPairs(DNode* head, int target) {
    DNode* left = head;
    DNode* right = head;
    
    // Move right to end
    while(right->next != nullptr) {
        right = right->next;
    }
    
    while(left != right && left->prev != right) {
        int sum = left->data + right->data;
        
        if(sum == target) {
            cout << "(" << left->data << ", " << right->data << ")" << endl;
            left = left->next;
            right = right->prev;
        }
        else if(sum < target) {
            left = left->next;
        }
        else {
            right = right->prev;
        }
    }
}
```

#### 2. Remove Duplicates from Sorted DLL
```cpp
DNode* removeDuplicates(DNode* head) {
    if(head == nullptr) return nullptr;
    
    DNode* current = head;
    
    while(current->next != nullptr) {
        if(current->data == current->next->data) {
            DNode* toDelete = current->next;
            current->next = current->next->next;
            if(current->next != nullptr) {
                current->next->prev = current;
            }
            delete toDelete;
        } else {
            current = current->next;
        }
    }
    
    return head;
}
```

---

## Day 27-28: Circular Linked List

### Day 27: Circular LL Basics

#### Node Structure (Same as Singly LL)
```cpp
struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};
```

#### 1. Insert in Empty List
```cpp
Node* insertEmpty(Node* last, int data) {
    if(last != nullptr) return last;
    
    Node* newNode = new Node(data);
    newNode->next = newNode;
    last = newNode;
    return last;
}
```

#### 2. Insert at Beginning
```cpp
Node* insertAtBegin(Node* last, int data) {
    if(last == nullptr) {
        return insertEmpty(last, data);
    }
    
    Node* newNode = new Node(data);
    newNode->next = last->next;
    last->next = newNode;
    return last;
}
```

#### 3. Insert at End
```cpp
Node* insertAtEnd(Node* last, int data) {
    if(last == nullptr) {
        return insertEmpty(last, data);
    }
    
    Node* newNode = new Node(data);
    newNode->next = last->next;
    last->next = newNode;
    last = newNode;
    return last;
}
```

#### 4. Delete Node
```cpp
Node* deleteNode(Node* last, int key) {
    if(last == nullptr) return nullptr;
    
    // If only one node
    if(last->data == key && last->next == last) {
        delete last;
        return nullptr;
    }
    
    Node* temp = last;
    Node* prev = nullptr;
    
    // If last node is to be deleted
    if(last->data == key) {
        while(temp->next != last) {
            temp = temp->next;
        }
        temp->next = last->next;
        delete last;
        return temp;
    }
    
    // Find node to delete
    while(temp->next != last && temp->next->data != key) {
        temp = temp->next;
    }
    
    if(temp->next->data == key) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
    
    return last;
}
```

#### 5. Display
```cpp
void display(Node* last) {
    if(last == nullptr) return;
    
    Node* temp = last->next;
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while(temp != last->next);
    cout << "(back to start)" << endl;
}
```

---

### Day 28: Advanced Problems

#### 1. Split Circular LL into Two Halves
```cpp
void splitList(Node* head, Node** head1, Node** head2) {
    Node* slow = head;
    Node* fast = head;
    
    // Find middle
    while(fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // If even number of nodes
    if(fast->next->next == head) {
        fast = fast->next;
    }
    
    *head1 = head;
    *head2 = slow->next;
    
    // Make first half circular
    slow->next = *head1;
    
    // Make second half circular
    fast->next = *head2;
}
```

#### 2. Check if Linked List is Circular
```cpp
bool isCircular(Node* head) {
    if(head == nullptr) return true;
    
    Node* temp = head->next;
    while(temp != nullptr && temp != head) {
        temp = temp->next;
    }
    
    return (temp == head);
}
```

#### 3. Josephus Problem
```cpp
int josephus(int n, int k) {
    Node* head = new Node(1);
    Node* prev = head;
    
    for(int i = 2; i <= n; i++) {
        prev->next = new Node(i);
        prev = prev->next;
    }
    prev->next = head;  // Make circular
    
    Node* ptr1 = head;
    Node* ptr2 = head;
    
    while(ptr1->next != ptr1) {
        int count = 1;
        while(count != k) {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            count++;
        }
        
        ptr2->next = ptr1->next;
        delete ptr1;
        ptr1 = ptr2->next;
    }
    
    return ptr1->data;
}
```

---

## Linked List vs Array

| Feature | Array | Linked List |
|---------|-------|-------------|
| Size | Fixed | Dynamic |
| Memory | Contiguous | Non-contiguous |
| Access | O(1) | O(n) |
| Insert at beginning | O(n) | O(1) |
| Insert at end | O(1) | O(n) without tail pointer |
| Delete | O(n) | O(1) if node pointer given |
| Memory overhead | No extra | Extra for pointers |
| Cache performance | Better | Worse |

---

## When to Use Linked Lists?

### Use Linked List When:
- Frequent insertions/deletions at beginning
- Size is unknown or changes frequently
- Don't need random access
- Implementing stack, queue, graph adjacency list

### Use Array When:
- Need random access
- Size is known and fixed
- Memory is limited (no pointer overhead)
- Cache performance matters

---

## Practice Problems (Week 4)

### Day 22: Singly LL Basics (4 problems)
1. Implement insert at head, tail, position
2. Implement delete operations
3. Search element in linked list
4. Find length of linked list

### Day 23: Singly LL Operations (4 problems)
5. Reverse linked list (iterative)
6. Reverse linked list (recursive)
7. Find middle element
8. Remove duplicates from sorted list

### Day 24: Singly LL Advanced (4 problems)
9. Detect cycle in linked list
10. Remove nth node from end
11. Merge two sorted lists
12. Check if linked list is palindrome

### Day 25: Doubly Linked List (4 problems)
13. Implement DLL with all operations
14. Reverse doubly linked list
15. Delete node in DLL (given node pointer)
16. Remove duplicates from sorted DLL

### Day 26: DLL Advanced (4 problems)
17. Find pairs with given sum in DLL
18. Sort DLL using merge sort
19. Rotate DLL by n nodes
20. Clone a linked list with random pointer

### Day 27: Circular Linked List (3 problems)
21. Implement circular linked list
22. Split circular LL into two halves
23. Check if linked list is circular

### Day 28: Mixed Problems (7 problems)
24. Josephus problem
25. Add two numbers represented by linked lists
26. Intersection point of two linked lists
27. Reverse in groups of k
28. Flatten a multilevel linked list
29. Sort linked list (merge sort)
30. LRU Cache implementation

---

## Common Patterns

### 1. Two Pointer Technique
- Fast and slow pointers (cycle detection, middle element)
- Two pointers from different lists (intersection)

### 2. Dummy Node
- Simplifies edge cases
- Used in merge operations

### 3. Recursion
- Reverse linked list
- Merge sorted lists
- Tree-like operations

### 4. Hash Map
- Detect cycle (store visited nodes)
- Clone with random pointer

---

## Important Points to Remember

### Memory Management
```cpp
// Always delete nodes to prevent memory leak
Node* temp = head;
head = head->next;
delete temp;  // Don't forget this!
```

### Edge Cases
- Empty list (head == nullptr)
- Single node
- Two nodes
- Operation at boundaries (first/last node)

### Common Mistakes
1. Not updating head pointer
2. Memory leaks (not deleting nodes)
3. Losing reference to nodes
4. Not handling nullptr cases
5. Infinite loops in circular lists

---

## Week 4 Checklist

- [ ] Understand node structure and pointers
- [ ] Implement all insertion operations
- [ ] Implement all deletion operations
- [ ] Master reverse linked list (both ways)
- [ ] Understand fast-slow pointer technique
- [ ] Implement doubly linked list
- [ ] Implement circular linked list
- [ ] Solve 25-30 problems
- [ ] Can explain when to use LL vs Array

---

## Tips for Linked List Problems

1. **Draw diagrams** - Always visualize pointer changes
2. **Handle edge cases first** - nullptr, single node
3. **Use dummy node** - Simplifies many operations
4. **Check for cycles** - Before traversing unknown lists
5. **Practice pointer manipulation** - Core skill for LL

---

## Revision Questions

1. How to reverse a linked list?
2. How to detect cycle?
3. How to find middle element?
4. Difference between singly and doubly LL?
5. When to use circular linked list?
6. How to merge two sorted lists?
7. How to remove nth node from end?

---

**Next Week:** Stack & Queue - We'll use linked lists to implement these!
