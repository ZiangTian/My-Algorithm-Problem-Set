# LeetCode 200

## Data Structure

In essence the problem exploits the math property of loops, and the key is finding an equation.  Many problems derive from mathematical ones and the solution is in a key equation.

```c++
public ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode *l1 = headA, *l2 = headB;
    while (l1 != l2) {
        l1 = l1 ? l1->next : headB;
        l2 = l2 ? l2->next : headA;
    }
    return l1;
}
```

Note that in this solution, the iterating condition is `l1 == nullptr` rather than `l1->next == nullptr`, in which case when `l1` hits the end and becomes `nullptr` the loop gets stuck.