# Singly Linked List — Full Revision Notes

This file covers **only singly linked lists**: definitions, basic CRUD, classic algorithms (reverse, cycle, merge), dummy nodes, interview checklists, and pitfalls—use it for notes and job prep in one place.

---

## 1. Core idea

- **Linear** structure; each **node** stores `data` and exactly **one** pointer `next`.
- Nodes are **not** necessarily contiguous in memory—no O(1) index access like arrays.
- Size is **dynamic**; insert/delete at the **front** is cheap compared to arrays.
- The list is usually referenced by a **`head`** pointer (`head == nullptr` means empty).

---

## 2. Node structure (C++)

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    explicit Node(int val) : data(val), next(nullptr) {}
};
```

---

## 3. Traversal and helpers

### 3.1 Print / traverse

**Time:** O(n), **Space:** O(1)

```cpp
void display(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}
```

### 3.2 Length

```cpp
int getLength(Node* head) {
    int count = 0;
    for (Node* t = head; t != nullptr; t = t->next)
        ++count;
    return count;
}
```

### 3.3 Search (value present?)

```cpp
bool search(Node* head, int val) {
    for (Node* t = head; t != nullptr; t = t->next) {
        if (t->data == val) return true;
    }
    return false;
}
```

---

## 4. Insert operations

### 4.1 Insert at head

**Time:** O(1)

```cpp
Node* insertAtHead(Node* head, int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    return newNode;  // new head
}
```

### 4.2 Insert at tail (no tail pointer)

**Time:** O(n) — walk to the end.

```cpp
Node* insertAtTail(Node* head, int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) return newNode;

    Node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;
    temp->next = newNode;
    return head;
}
```

### 4.3 Insert at position (0 = head)

**Time:** O(n)

```cpp
Node* insertAtPosition(Node* head, int data, int pos) {
    if (pos == 0) return insertAtHead(head, data);

    Node* newNode = new Node(data);
    Node* temp = head;
    for (int i = 0; i < pos - 1 && temp != nullptr; ++i)
        temp = temp->next;

    if (temp == nullptr) {
        delete newNode;
        return head;  // invalid position
    }

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}
```

---

## 5. Delete operations

Do not use a pointer after `delete` in C++.

### 5.1 Delete from head

```cpp
Node* deleteFromHead(Node* head) {
    if (head == nullptr) return nullptr;
    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}
```

### 5.2 Delete from tail

```cpp
Node* deleteFromTail(Node* head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) {
        delete head;
        return nullptr;
    }
    Node* temp = head;
    while (temp->next->next != nullptr)
        temp = temp->next;
    delete temp->next;
    temp->next = nullptr;
    return head;
}
```

### 5.3 Delete first node with given value

```cpp
Node* deleteByValue(Node* head, int val) {
    if (head == nullptr) return nullptr;
    if (head->data == val) return deleteFromHead(head);

    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != val)
        temp = temp->next;

    if (temp->next == nullptr) return head;

    Node* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
    return head;
}
```

### 5.4 Delete at position

```cpp
Node* deleteAtPosition(Node* head, int pos) {
    if (head == nullptr) return nullptr;
    if (pos == 0) return deleteFromHead(head);

    Node* temp = head;
    for (int i = 0; i < pos - 1 && temp != nullptr; ++i)
        temp = temp->next;

    if (temp == nullptr || temp->next == nullptr) return head;

    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete;
    return head;
}
```

---

## 6. Remove duplicates from a sorted list

**Precondition:** list is sorted non-decreasing.

```cpp
Node* removeDuplicatesSorted(Node* head) {
    if (head == nullptr) return nullptr;
    Node* cur = head;
    while (cur->next != nullptr) {
        if (cur->data == cur->next->data) {
            Node* junk = cur->next;
            cur->next = junk->next;
            delete junk;
        } else {
            cur = cur->next;
        }
    }
    return head;
}
```

---

## 7. Reverse linked list

### 7.1 Iterative — O(1) extra space

```cpp
Node* reverseIterative(Node* head) {
    Node* prev = nullptr;
    Node* cur = head;
    while (cur != nullptr) {
        Node* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}
```

### 7.2 Recursive — O(n) stack

```cpp
Node* reverseRecursive(Node* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    Node* newHead = reverseRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}
```

**Idea:** after recursion, `head->next` is the node that becomes the successor in the reversed tail; point its `next` back to `head`.

---

## 8. Middle node (slow / fast)

When `fast` cannot advance, `slow` is the middle (for even length, usually the **second** middle).

```cpp
Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

**Variation:** change advance/stop rules to return the **first** middle on even length—match the problem statement.

---

## 9. Cycle detection (Floyd)

Tortoise and hare: `slow` steps 1, `fast` steps 2. If they meet, there is a **cycle**.

```cpp
bool hasCycle(Node* head) {
    if (head == nullptr) return false;
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

### 9.1 Start node of the cycle (extra)

Steps:

1. Find meeting point `meet` (same loop, exit before pointers meet until condition breaks).
2. Advance one pointer from `head` and one from `meet` one step at a time; where they meet is the **entry** of the cycle.

(Proof uses distance equations—good to know for interviews.)

---

## 10. Remove nth node from end (dummy head)

**Time:** O(n), **Space:** O(1). A `dummy` head unifies “delete first node” with the general case.

```cpp
Node* removeNthFromEnd(Node* head, int n) {
    Node* dummy = new Node(0);
    dummy->next = head;
    Node* first = dummy;
    Node* second = dummy;

    for (int i = 0; i <= n; ++i)
        first = first->next;

    while (first != nullptr) {
        first = first->next;
        second = second->next;
    }

    Node* toDelete = second->next;
    second->next = second->next->next;
    delete toDelete;

    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}
```

**Why dummy:** if `n == length`, you delete the real head—starting `second` at dummy avoids extra branching.

---

## 11. Merge two sorted lists

New nodes optional; rewiring existing nodes is enough.

```cpp
Node* mergeSortedLists(Node* l1, Node* l2) {
    Node dummy(0);
    Node* tail = &dummy;

    while (l1 != nullptr && l2 != nullptr) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = (l1 != nullptr) ? l1 : l2;
    return dummy.next;
}
```

---

## 12. Array vs singly linked list

| Feature | Array / vector | Singly LL |
|---------|----------------|-----------|
| Size | Fixed or capacity-growth | Dynamic |
| Memory layout | Contiguous | Scattered + pointer overhead |
| i-th access | O(1) | O(n) |
| Insert at front | O(n) | O(1) |
| Insert at back | Amortized O(1) for vector | O(n) without tail pointer |
| Cache friendliness | Better | Worse |

---

## 13. When to use linked lists

- Many insert/delete at the **front**.
- Unknown or rapidly changing size.
- No need for random access.
- Implementing stack, queue, or graph adjacency lists.

---

## 14. Common patterns

| Pattern | Uses |
|---------|------|
| Slow / fast | Middle, cycle, split |
| Dummy node | Merge, nth-from-end, partition |
| Prev / cur / next | Reverse, insert |
| Hash set / map | Visited sets, clone with random pointer (helper) |

---

## 15. Interview checklist (singly focus)

**Basics**

- [ ] Insert at head / tail / position
- [ ] Delete head / tail / value / position
- [ ] Length, search, print
- [ ] Remove duplicates from sorted list

**Classic**

- [ ] Reverse (iterative + recursive)
- [ ] Middle node
- [ ] Detect cycle (+ entry node optional)
- [ ] Remove nth from end
- [ ] Merge sorted lists

**Common follow-ups**

- [ ] Palindrome linked list (half-reverse or stack)
- [ ] Intersection of two linked lists
- [ ] Reverse in groups of k
- [ ] Add two numbers as lists
- [ ] Merge sort on linked list

---

## 16. Edge cases and common bugs

- `head == nullptr`, single node, two nodes.
- Delete/update **first or last** node.
- Invalid `pos` or `n > length`.
- Cycle: naive `while (temp)` may run forever.
- Forgetting to **return / assign new `head`** from mutating functions.
- **Dangling pointers** or leaks after unlink (`delete`).

---

## 17. Destroy whole list (cleanup)

```cpp
void destroyList(Node*& head) {
    while (head != nullptr) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}
```

---

## 18. Revision questions

1. How do you reverse a singly linked list in O(1) extra space?
2. Why does Floyd’s cycle detection work?
3. Why is a dummy node helpful for “remove nth from end”?
4. How does changing slow/fast stop rules change the “middle” on even length?
5. With a tail pointer, which operations become O(1)?

---

*Doubly and circular lists: see `doubly-linked-list.md` and `circular-linked-list.md`.*
