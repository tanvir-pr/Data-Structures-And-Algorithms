# Circular Linked List — Full Revision Notes

This file covers **only circular linked lists** (usually **singly circular**): the `last` pointer pattern, empty/single-node cases, full insert/delete/display code, split in two, circular checks, Josephus, accidental cycle vs intentional ring, complexity, and checklists.

---

## 1. Idea

- In a normal singly list the **last** `next` is `nullptr`.
- In a **circular** list the last node **links back to the first**—a ring.
- Many APIs store **`last`** (tail); then **`last->next` is the first node (logical head)**.
- **Empty:** `last == nullptr`.
- **One node:** `node->next == node`.

---

## 2. Node (same as singly)

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

## 3. Why keep `last`?

- **Known `last`:**
  - **Insert at beginning:** `new->next = last->next; last->next = new` — O(1)
  - **Insert at end:** same link step, then `last = new` — O(1)
- With only `head`, inserting at the **end** may require walking the whole ring—`last` optimizes that.

---

## 4. First node into empty list

```cpp
Node* insertEmpty(Node* last, int data) {
    if (last != nullptr) return last;

    Node* nn = new Node(data);
    nn->next = nn;
    return nn;  // single-node ring; this is last
}
```

---

## 5. Insert at beginning

Use `insertEmpty` when `last` is null.

```cpp
Node* insertAtBegin(Node* last, int data) {
    if (last == nullptr)
        return insertEmpty(last, data);

    Node* nn = new Node(data);
    nn->next = last->next;
    last->next = nn;
    return last;
}
```

**Where is head?** `last->next` is always the **first** node.

---

## 6. Insert at end

```cpp
Node* insertAtEnd(Node* last, int data) {
    if (last == nullptr)
        return insertEmpty(last, data);

    Node* nn = new Node(data);
    nn->next = last->next;
    last->next = nn;
    return nn;  // new tail
}
```

---

## 7. Traverse / display

Start at `first = last->next`; use **do-while** for one full round.

```cpp
void display(Node* last) {
    if (last == nullptr) return;

    Node* first = last->next;
    Node* t = first;
    do {
        cout << t->data << " -> ";
        t = t->next;
    } while (t != first);
    cout << "(back to start)\n";
}
```

**Length:**

```cpp
int length(Node* last) {
    if (last == nullptr) return 0;
    int c = 0;
    Node* first = last->next;
    Node* t = first;
    do {
        ++c;
        t = t->next;
    } while (t != first);
    return c;
}
```

---

## 8. Delete by key (tutorial-style, case-heavy)

```cpp
Node* deleteNode(Node* last, int key) {
    if (last == nullptr) return nullptr;

    // Only node in list and it matches
    if (last->data == key && last->next == last) {
        delete last;
        return nullptr;
    }

    Node* prev = last;
    Node* cur = last->next;  // start at logical head

    do {
        if (cur->data == key) {
            if (cur == last)
                last = prev;  // new last (previous node)

            prev->next = cur->next;
            delete cur;
            return last;
        }
        prev = cur;
        cur = cur->next;
    } while (cur != last->next);

    return last;
}
```

Other implementations may differ in tail updates—**keep the ring valid**; a lone survivor must satisfy `next = self`.

**Practice:** draw cases and verify `last` after every delete.

---

## 9. Split circular list into two halves (slow / fast)

Here **`head`** is the **first** node of the circular list (reference implementation). If you only have `last`, set `head = last->next` first.

**Idea:** slow/fast finds **middle**; first half ends at `slow`; second half starts at `slow->next`. Close two separate rings: `slow->next = head1`, tail of second half `fast` links to `head2`.

```cpp
// head = start of circular list; outputs heads of two circular lists
void splitCircularIntoTwo(Node* head, Node** head1, Node** head2) {
    if (head == nullptr) {
        *head1 = *head2 = nullptr;
        return;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Even length: advance fast one step (standard trick)
    if (fast->next->next == head)
        fast = fast->next;

    *head1 = head;
    *head2 = slow->next;

    slow->next = *head1;   // first half circular
    fast->next = *head2;   // second half circular
}
```

**After reading:** trace 1,2,3,… nodes by hand; check `slow`/`fast` stops and `head1`/`head2`. If your API uses `last`, walk once from `head2` to find the second list’s tail.

---

## 10. Is list circular? (given `head` as first node)

Assume **circular** means you eventually return to `head` without hitting `nullptr`.

```cpp
bool isCircular(Node* head) {
    if (head == nullptr) return false;  // tune per problem statement
    Node* t = head->next;
    while (t != nullptr && t != head)
        t = t->next;
    return (t == head);
}
```

Some problems define empty differently—**read the statement**.

---

## 11. Accidental cycle vs structural circular

| | Intentional CLL | Accidental cycle in normal list |
|--|-----------------|----------------------------------|
| Purpose | Design | Bug |
| Detection | Floyd works | Same |
| Traverse | do-while or bounded count | Naive `while` may not terminate |

---

## 12. Josephus (CLL simulation)

`n` people; each round count `k` steps, remove that node.

```cpp
int josephus(int n, int k) {
    if (n <= 0) return -1;

    Node* head = new Node(1);
    Node* prev = head;
    for (int i = 2; i <= n; ++i) {
        prev->next = new Node(i);
        prev = prev->next;
    }
    prev->next = head;

    Node* cur = head;
    Node* pre = prev;

    while (cur->next != cur) {
        for (int i = 1; i < k; ++i) {
            pre = cur;
            cur = cur->next;
        }
        pre->next = cur->next;
        delete cur;
        cur = pre->next;
    }
    int ans = cur->data;
    delete cur;
    return ans;
}
```

**Time:** O(n·k) for this simulation; closed-form recurrence exists (advanced).

---

## 13. Complexity

| Operation | Time (typical with `last`) |
|-----------|------------------------------|
| Insert begin/end | O(1) |
| Delete by key | O(n) |
| Length / search | O(n) |
| Display | O(n) |

---

## 14. Real-world uses

- Round-robin scheduling.
- Ring buffer (circular queue).
- Games / elimination (Josephus).
- Repeated traversal where “after last comes first” is natural.

---

## 15. Interview checklist

- [ ] Draw `last`-based representation
- [ ] Insert begin/end for empty, one, many nodes
- [ ] do-while traversal
- [ ] Delete with hard cases
- [ ] Split two halves (slow/fast stopping)
- [ ] `isCircular`
- [ ] Josephus (basic simulation)

---

## 16. Edge cases and pitfalls

- `last == nullptr` vs one node `last->next == last`.
- Forgetting to **update `last`** after delete.
- Expecting `nullptr` to end traversal—infinite loop usually means **wrong stop condition** on a ring.
- After split, both parts must remain valid circles.

---

## 17. Revision questions

1. Why do many CLL APIs store `last` instead of `head`?
2. Why use `do-while` for display instead of a simple `while`?
3. Why is a circular structure natural for Josephus?
4. How do slow/fast stop conditions differ from a plain singly list when the list is circular?

---

*Related: `singly-linked-list.md`, `doubly-linked-list.md`.*
