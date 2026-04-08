# Doubly Linked List — Full Revision Notes

This file covers **only doubly linked lists**: `prev` and `next`, full code for basic ops, reverse, two-pointer from both ends, duplicate removal, LRU idea, complexity, and checklists.

---

## 1. Why use a DLL?

- You can walk **backward**—`prev` exists.
- If you know a **node’s address**, delete/insert is often **O(1)** (singly usually needs the predecessor).
- **Trade-off:** extra pointer per node—more memory; you must keep **symmetric** link invariants.

---

## 2. Node structure

```cpp
#include <iostream>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;

    explicit DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};
```

---

## 3. Invariants (memorize)

After **any** link change:

1. If `x->next == y`, then usually `y->prev == x` (if `y` exists).
2. If `x->prev == y`, then usually `y->next == x`.
3. The **head’s** `prev` should stay `nullptr`.
4. Updating only one direction breaks the list or causes subtle bugs.

---

## 4. Traversal: forward and backward

### 4.1 Forward

```cpp
void displayForward(DNode* head) {
    DNode* t = head;
    while (t != nullptr) {
        cout << t->data << " <-> ";
        t = t->next;
    }
    cout << "NULL\n";
}
```

### 4.2 Backward (from head: go to tail, then walk `prev`)

```cpp
void displayBackward(DNode* head) {
    if (head == nullptr) return;
    DNode* t = head;
    while (t->next != nullptr)
        t = t->next;
    while (t != nullptr) {
        cout << t->data << " <-> ";
        t = t->prev;
    }
    cout << "NULL\n";
}
```

**Note:** if you store a `tail` pointer, backward walk is just `tail` and repeated `prev`.

---

## 5. Insert

### 5.1 At head

```cpp
DNode* insertAtHead(DNode* head, int data) {
    DNode* nn = new DNode(data);
    if (head == nullptr) return nn;
    nn->next = head;
    head->prev = nn;
    return nn;
}
```

### 5.2 At tail

```cpp
DNode* insertAtTail(DNode* head, int data) {
    DNode* nn = new DNode(data);
    if (head == nullptr) return nn;

    DNode* t = head;
    while (t->next != nullptr) t = t->next;
    t->next = nn;
    nn->prev = t;
    return head;
}
```

### 5.3 After a node (`cur` must be non-null)

```cpp
void insertAfter(DNode* cur, int data) {
    if (cur == nullptr) return;
    DNode* nn = new DNode(data);
    nn->next = cur->next;
    nn->prev = cur;
    if (cur->next != nullptr)
        cur->next->prev = nn;
    cur->next = nn;
}
```

### 5.4 Before a node (or use `insertAfter(cur->prev, ...)` when not head)

```cpp
DNode* insertBefore(DNode* head, DNode* cur, int data) {
    if (cur == nullptr) return head;
    if (cur == head) return insertAtHead(head, data);

    DNode* nn = new DNode(data);
    DNode* p = cur->prev;
    nn->prev = p;
    nn->next = cur;
    p->next = nn;
    cur->prev = nn;
    return head;
}
```

---

## 6. Delete node (known pointer — LeetCode style)

```cpp
DNode* deleteNode(DNode* head, DNode* del) {
    if (head == nullptr || del == nullptr) return head;

    if (del == head)
        head = del->next;

    if (del->next != nullptr)
        del->next->prev = del->prev;
    if (del->prev != nullptr)
        del->prev->next = del->next;

    delete del;
    return head;
}
```

**Time:** O(1) when `del` is known.

---

## 7. Delete first node with given value

```cpp
DNode* deleteByValue(DNode* head, int val) {
    for (DNode* t = head; t != nullptr; t = t->next) {
        if (t->data == val) return deleteNode(head, t);
    }
    return head;
}
```

---

## 8. Reverse DLL (no new nodes — swap links)

```cpp
DNode* reverse(DNode* head) {
    DNode* cur = head;
    DNode* newHead = nullptr;

    while (cur != nullptr) {
        DNode* nxt = cur->next;
        cur->next = cur->prev;
        cur->prev = nxt;
        newHead = cur;
        cur = nxt;
    }
    return newHead;
}
```

**Sanity check:** draw a 2–3 node list and verify every `prev`/`next`.

---

## 9. Remove duplicates from sorted DLL

```cpp
DNode* removeDuplicatesSorted(DNode* head) {
    if (head == nullptr) return nullptr;
    DNode* cur = head;

    while (cur->next != nullptr) {
        if (cur->data == cur->next->data) {
            DNode* junk = cur->next;
            cur->next = junk->next;
            if (cur->next != nullptr)
                cur->next->prev = cur;
            delete junk;
        } else {
            cur = cur->next;
        }
    }
    return head;
}
```

---

## 10. Sorted DLL: pairs that sum to target (two pointers)

`left = head`, `right` at tail; shrink interval by sum vs target.

```cpp
void findPairsWithSum(DNode* head, int target) {
    if (head == nullptr) return;
    DNode* left = head;
    DNode* right = head;
    while (right->next != nullptr) right = right->next;

    while (left != nullptr && right != nullptr && left != right &&
           right->next != left) {
        int s = left->data + right->data;
        if (s == target) {
            cout << "(" << left->data << ", " << right->data << ")\n";
            left = left->next;
            right = right->prev;
        } else if (s < target) {
            left = left->next;
        } else {
            right = right->prev;
        }
    }
}
```

**Loop stop:** tune for duplicate pairs / odd length as the problem requires.

---

## 11. LRU cache (concept — very common)

- **Hash map:** `key` → `DNode*` (address of node in list).
- **DLL:** encodes order—recent near **head**, eviction from **tail**.
- `get` / `put`: move node or insert new at head; if at capacity, delete tail and erase from map.

Not “DLL only”—but **DLL + map** is the standard design to internalize.

---

## 12. Complexity summary

| Operation | Time | Notes |
|-----------|------|-------|
| Insert at head | O(1) | |
| Insert at tail without tail ptr | O(n) | |
| Insert/delete at known node | O(1) | |
| Access i-th | O(n) | |
| Search by value | O(n) | |

---

## 13. Singly vs doubly

| | Singly | Doubly |
|--|--------|--------|
| Pointer overhead | 1 / node | 2 / node |
| Backward traverse | No | Yes |
| Unlink with only node ptr | Often need prev | Easy |

---

## 14. Interview checklist (DLL)

- [ ] Insert at head/tail, delete by node pointer
- [ ] Print forward/backward
- [ ] Reverse DLL
- [ ] Remove duplicates from sorted DLL
- [ ] Two-sum style with two ends
- [ ] (Optional) Flatten multilevel doubly linked list
- [ ] Explain LRU-style design

---

## 15. Edge cases and bugs

- Empty list, single node.
- Delete head/tail—update `head`.
- Forgetting `cur->next->prev` breaks links.
- After reverse, return the **new head**.

---

## 16. Cleanup

```cpp
void destroyList(DNode*& head) {
    while (head != nullptr) {
        DNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}
```

---

## 17. Revision questions

1. Why is `delete(target)` usually O(1) in a DLL?
2. Why does `deleteNode` check head, `prev`, and `next` neighbors?
3. Where is the new head set in `reverse`?
4. Why LRU uses DLL plus a map, not a queue alone?

---

*Related: `singly-linked-list.md`, `circular-linked-list.md`.*
