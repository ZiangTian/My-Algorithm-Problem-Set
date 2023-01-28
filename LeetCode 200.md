# LeetCode 200

## Data Structure

### 160  Intersection of Two Linked Lists (Easy)

In essence the problem exploits the math property of loops, and the key is finding an equation.  Many problems derive from mathematical ones and the solution is in a key equation.

```c++
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode *l1 = headA, *l2 = headB;
    while (l1 != l2) {
        l1 = l1 ? l1->next : headB;
        l2 = l2 ? l2->next : headA;
    }
    return l1;
}
```

**Note that in this solution, the iterating condition is `l1 == nullptr` rather than `l1->next == nullptr`, in which case when `l1` hits the end and becomes `nullptr` the loop gets stuck.**

### 206 Reverse Linked List (Easy)

Recursive solution: This requires us to  write the exit at the top of the entry. Bear in mind that head, after the function, should be at the end of the list, pointing to nullptr.

The function can roughly be divided into 4 steps:

- exit
- send the next node into recursion
- after recursion, **`newHead` is the head of a partially reversed list**. **`tmp` is at the tail of this partially reversed list**. **`head` is right before this list**. Therefore, point last node (denoted as `tmp`) to `head` and set `head` to `nullptr`
- return `newHead`

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) { 
        // suppose we're dealing with 1->5->4->3->2
        if(!head || !head->next) return head;
        ListNode* tmp = head->next;  
        ListNode* newHead = reverseList(tmp)
        tmp->next = head;
        head->next = nullptr;
        return newHead;
    }
};
```

> For any confusion with Recursion, [this website](https://lyl0724.github.io/2020/01/25/1/) does a good job explaining it. 

### 19 Remove Nth Node From the End of List (Medium)

#### *Sol1: Stack*

While iterating through the list, push the nodes into a stack (FILO), which means the n-th popped node is the one to be deleted, and that the node currently on top of the stack is the prenode of it.

```c++
 #include<stack>
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        stack<ListNode*> st;
        ListNode* p = head;
        while(p){
            st.push(p);
            p = p->next;
        }
        while(!st.empty() && n>0){
            p = st.top(); st.pop();
            n--;
        }
        if(st.empty()){
            // p points to head, which should be deleted
            head = head->next;
        }
        else{ 
            ListNode* q = st.top();
            q->next = p->next;
        }
        delete p;
        p = nullptr;
        return head;
    }
};
```

Note that it is even better to use a dummyHead as shown in the [official solution,](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/solution/shan-chu-lian-biao-de-dao-shu-di-nge-jie-dian-b-61/) which saves the trouble of ascertaining whether the stack is empty.

#### *Sol2: Double pointers*

Use two pointers, `first` and `second` to iterate over the list, with `first` starting first and `second` starting off when `first` has gone over n nodes. In this way, when `first` hits the tail, `second` will be at the target node.

```C++
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head), *first = head, *second = dummy;
        for(int i=0;i<n;i++) first = first->next;
        while(first){
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        ListNode* h = dummy->next;
        delete dummy;
        return h;
    }
};
```

