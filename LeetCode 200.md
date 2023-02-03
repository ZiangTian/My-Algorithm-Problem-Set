# LeetCode 200

[TOC]

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

### 24. Swap Nodes in Pairs (Medium)

#### ***Sol1: Recursion***

> Three considerations when using a recursive structure:
>
> 1.  terminating condition (the exit)? 
> 2. what should current level of recursion return to its prior level?
> 3. what should be implemented in this level of recursion?

```C++
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // exit: a nullptr or the tail
        if(!head || !head->next) return head;
        ListNode* q = head->next;
        // return a modified list to the prior level (for its node to point to as next)
        // we switch the two nodes (current node and the next one) on this level of recursion. Note that the current node should point to the modified list.
        head->next = swapPairs(q->next);
        q->next = head;
        return q;
    }
};
```

#### *Sol2: Iteration*

In this non-recursive solution, 3 pointers (temp, node1, node2 respectively) are used and a dummy head is added. The interaction between these pointers can get confusing:

The node pointed by temp does not get switched. Rather, temp is meant to keep track of the preceding node of node1. After each iteration, **temp is renewed to point at node 1**, after which **node 1 and node 2 progress to the right of temp**. **Initially temp points at the dummy head**.

```C++
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* temp = dummyHead;
        while (temp->next != nullptr && temp->next->next != nullptr) {
            ListNode* node1 = temp->next;
            ListNode* node2 = temp->next->next;
            temp->next = node2;
            node1->next = node2->next;
            node2->next = node1;
            temp = node1;
        }
        return dummyHead->next;
    }
};
```

### 445. Add Two Numbers II (Medium)

#### ***Sol1: Reverse the list with recursion***

```C++
class Solution {
public:
    ListNode* flip(ListNode* h){
        if(!h || !h->next) return h;
        ListNode* p = h->next;
        ListNode* tmp = flip(p);
        p->next = h;
        h->next = nullptr;  // KEY! without this the list would be messed up.
        return tmp;
    }
  
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* h1 = flip(l1), *h2 = flip(l2);
        ListNode* p1 = h1, *p2 = h2;
        int new_val, digit, carry = 0;
        ListNode* dummy = new ListNode(0);
        ListNode* p = dummy;
        while(p1 && p2){
            new_val = p1->val + p2->val + carry;
            digit = new_val%10; 
            carry = new_val/10;
            ListNode* tmp = new ListNode(digit);
            p->next = tmp;
            p = p->next;

            p1 = p1->next;
            p2 = p2->next;
        }
        while(p1){ // handle remaining p1
            new_val = p1->val + carry;
            digit = new_val%10;
            carry = new_val/10;
            ListNode* tmp = new ListNode(digit);

            p->next = tmp;
            p = p->next;
            p1 = p1->next;            
        }
        while(p2){ 
            new_val = p2->val + carry;
            digit = new_val%10;
            carry = new_val/10;
            ListNode* tmp = new ListNode(digit);

            p->next = tmp;
            p = p->next;
            p2 = p2->next;
        }
        // Do not forget to handle one last possible carry
        if(carry){
            ListNode* tmp = new ListNode(carry);
            p->next = tmp;
        }
        ListNode* res = dummy->next;
        delete dummy;
        return flip(res);
    }
};
```

This solution should be very straightforward structurally, but there are two key points that can be of future reference:

- always remember to set the tail of a linked list to be nullptr.
- when handling bitwise addition, remember to add the last carry bit that often gets omitted in the loop

However, it should be intuitive to **use stack when handling reverse-order operation**, as shown in the following code:

#### *Sol2: Stack*

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1, s2;
        while (l1) {
            s1.push(l1 -> val);
            l1 = l1 -> next;
        }
        while (l2) {
            s2.push(l2 -> val);
            l2 = l2 -> next;
        }
        int carry = 0;
        ListNode* ans = nullptr;
        while (!s1.empty() or !s2.empty() or carry != 0) {
            int a = s1.empty() ? 0 : s1.top();
            int b = s2.empty() ? 0 : s2.top();
            if (!s1.empty()) s1.pop();
            if (!s2.empty()) s2.pop();
            int cur = a + b + carry;
            carry = cur / 10;
            cur %= 10;
            auto curnode = new ListNode(cur);
            curnode -> next = ans;
            ans = curnode;
        }
        return ans;
    }
};
```

Note that the order of the original list remains intact.

### 234. Palindrome Linked List (Easy)

#### *Sol1: Stack* 

Following the solutions of [Prob 445](https://leetcode.com/problems/add-two-numbers-ii/), [Prob 24](https://leetcode.com/problems/swap-nodes-in-pairs/), stack is our top consideration when handling this:

```C++
#include<stack>
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<ListNode*> st;
        ListNode* p = head, *q;
        while(p){
            st.push(p);
            p = p->next;
        }
        p = head;
        while(!st.empty()){
            q = st.top(); st.pop();
            if(p->val != q->val) return false;
            p = p->next;
        }
        return true;
    }
};
```

However, using stack here can be rather space-consuming. We may improve this by only comparing half of the nodes, but another way to tackle it is a combination of crucial tricks required for handling linked lists.

#### *Sol2: find_middle, reverse, and check*

We divide the designated task into several subtasks:

1. cutting the list in half  (by locating the middle node)

2. reversing the latter half

3. checking the pairs 

We use double pointers to find the middle node and recursion to reverse the list.

```C++
bool isPalindrome(ListNode* head) {
    ListNode* fast = head, *slow = head;
    //find middle node
    while (fast != null && fast.next != null) {
        fast = fast->next->next;
        slow = slow->next;
    }
    // if fast is not null, then there are odd number of nodes
    if (fast != null) {
        slow = slow->next;
    }
    // reverse latter half
    slow = reverse(slow);

    fast = head;
    while (slow != null) {
        if (fast->val != slow->val)
            return false;
        fast = fast->next;
        slow = slow->next;
    }
    return true;
}

// reverse
ListNode* reverse(ListNode* head) {
    ListNode* prev = null;
    while (head != null) {
        ListNode next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}
```

**A key takeaway is the method to locate the middle node in here. If `fast` is non-null, then point `slow` to the next node, which is exactly the middle node**.

### 725. Split Linked List in Parts(Medium)

I got into a bit of trouble in this one. 
$$
avg = \frac{len}{k}, 
rem = len\mod{k}
$$
**We divide the nodes into `k` groups, each containing  `avg` nodes with `rem` ones yet to be grouped. Assign the first `rem` groups with one extra node from the ungrouped.**

However, what got me was the loops. I went so far as to write three nested loops, which really made it all complicated. 

```C++
class Solution {
public:

    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int len = 0;
        ListNode*p = head;
        while(p){
            p = p->next;
            len++;
        }
        int avg = len/k;
        int rem = len%k;

        vector<ListNode*> parts(k,nullptr); // key! setting possible null pointers in advance
        ListNode* itr = head;
        for(int i=0; i<k && itr; i++){
            parts[i] = itr;
            int partSize = avg + (i<rem); // for the first rem groups, partSize is greater
            for(int j= 1; j< partSize; j++){
                itr = itr->next;
            }
            p = itr->next;
            itr->next = nullptr;
            itr = p;
        }

        return parts;
        
    }
};
```

Actually only 2 loops are needed: one for the outer iteration to fill all the non-null groups (now that the potential null nodes at the tail, if any, have been handled), and another for the iteration within the group. In fact, the second loop can be simply viewed as a pattern to skip a certain number of nodes, so there is really a single loop here.

> key takeway: learn to view loops from a different perspective.

### 104. Maximum Depth of Binary Tree (Easy)

#### *Sol1: BFS*

This code offers important insights on calculating the exact number of nodes on a level:

```c++
class Solution {
public:

    int maxDepth(TreeNode* root) {
        // BFS
        if(!root) return 0;
        TreeNode* p = root;
        queue<TreeNode*> qu;
        qu.push(p);
        int lev = 0;
        while(!qu.empty()){
            int curLev = qu.size();
            while(curLev>0){
                p = qu.front(); qu.pop();
                if(p->left) qu.push(p->left); 
                if(p->right)qu.push(p->right);
                curLev--; // number of nodes on current level
            }
            lev++;
        }
        return lev;
    }
};
```

In the code, every initial value of `curLev` is the number of nodes on current level.

#### *Sol2: DFS*

This should be more intuitive:

```c++
class Solution {
public:

    int maxDepth(TreeNode* root) {
        if (!root)return 0;
        else {
            int maxDepth1 = 1 + maxDepth(root->left);
            int maxDepth2 = 1 + maxDepth(root->right);
            return maxDepth1>maxDepth2 ? maxDepth1 : maxDepth2;
        }
    }
};
```

Note that by calling `maxDepth`, we are diving deeper into the tree, hence the increment of `maxDepth`.

### 110. Balanced Binary Tree (Easy)

My solution at first shot. For those "attribute-judging" problems, usually:

- determine the conditions for the attributes: is it a `&&` between all conditions or `||` ?
- the leftchild and (or) rightchild must satisfy such a condition in some way, and the relationship in between them must satisfy the attribute.

```C++
class Solution {
public:
    int getDep(TreeNode* r){
        if(!r) return 0;
        return max(getDep(r->left), getDep(r->right))+1;
    }
    bool okay(int a, int b){
        return (b-1 <= a && a <= b+1) ? true : false;
    }
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        return isBalanced(root->left) && isBalanced(root->right) && okay(getDep(root->left), getDep(root->right));
    }
};
```

However, it's obvious that this solution has gone to extra lengths as to calculate the depth of every node. To avoid this, consider *postorder traversal*: 

```C++
class Solution {
public:
    int height(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1)          return -1;
            else {
            return max(leftHeight, rightHeight) + 1;
        }
    }

    bool isBalanced(TreeNode* root) {
        return height(root) >= 0;
    }
};
```

### 543. Diameter of Binary Tree (Easy)

Things were pretty smooth with this one. After quite some analysis, the process got more straightforward:

- For any pair of nodes in a tree, there is and only is a single path between them.
- The longest path in a tree may or may not contain the ROOT, but **can always be found *diverging* from a certain "root"**. "Diverging" includes the case where a path spans directly from the root to the node.
- Therefore, for every node, there exists a regionally longest path that contains it. The length of this path is the sum of the **depths** of its child nodes.

```C++
class Solution {
public:
    int getDep(TreeNode* r){
        if(!r) return 0;
        return max(getDep(r->left), getDep(r->right))+1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        // exit
        if(!root) return 0;  
        // longest path running through current node
        int curDia = getDep(root->left) + getDep(root->right); 
        // longest path running through left child
        int leftDia = diameterOfBinaryTree(root->left); 
        // longest path running through right child
        int rightDia = diameterOfBinaryTree(root->right); 
        return max(curDia, max(leftDia, rightDia)); //must be among the three of them
    }
};
```

### 226. Invert Binary Tree (Easy)

This relatively easier one reinforces our skills of using recursion.

```C++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return nullptr;
        TreeNode* l = root->left, *r = root->right;
        root->right = l; root->left = r;
        invertTree(root->left); invertTree(root->right);
        return root;
    }
};
```

### 617. Merge Two Binary Trees (Easy)

I used to struggle with this one but now it's better. Identify our three goals:

1. recursion exit: when both pointers hit null
2. tasks within current level: combine current node; combine the children nodes
3. return value: the partially combined tree. here we should return the current node as it is the root of that tree. 

```C++
class Solution {
public:
    
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        // exit
        if(!(root1 || root2)) return nullptr; 
        
    // Task1 within current level: combine children nodes
        
        // If one of the node is nullptr, directly create a copy of another and return
        if(!root1) return new TreeNode(root2->val, root2->left, root2->right);
        if(!root2) return new TreeNode(root1->val, root1->left, root1->right);
        // If both exist, combine their chidlren
        TreeNode* mergedLeft = mergeTrees(root1->left, root2->left);
        TreeNode* mergedRight = mergeTrees(root1->right, root2->right),
        
    // Task2 within current level: merge current nodes
        TreeNode* newNode = new TreeNode(root1->val + root2->val);
        
    // Return the merged node
        newNode->left = mergedLeft;
        newNode->right = mergedRight;
        return newNode;
    }

};
```

> Note that we created a new, independent tree here rather than one with borrowed nodes from the previous trees.

### 112. Path Sum (Easy)

Again, I hit a rough patch with this one. I attempted to iterate all over the tree and find all paths from the root to the leaves with the following code (which worked out fine but got into a vague definition problem over whether the root node counts as a leaf node). It utilizes the property of the vector that automatically retires to its prior state in a recursion:

```C++
#include<vector>
using namespace std;
class Solution {
public:
    bool flag;
    vector<vector<int>> paths;
    void go2leaf(TreeNode* r, vector<int> path){
        // automatic retirement of path
        if(!r){
            // at the root
            if(path.size()>1) paths.push_back(path); // attempts to rule out the case where the root node counts as leaf node
            return;
        }
        else{
            path.push_back(r->val);
            go2leaf(r->left, path);
            go2leaf(r->right, path);
        }
    }
    int getSum(vector<int>& v){
        int i, len = v.size(), sum = 0;
        for(i = 0; i< len;  i++) sum += v[i];
        return sum;
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root) return false; 
        if(!root->left && !root->right) return root->val == targetSum;

        vector<int> path;
        go2leaf(root, path);  // find all paths that leads to all leaves. 

        int numOfleaf = paths.size();
        for(int i = 0; i<numOfleaf; i++)
            if(getSum(paths[i]) == targetSum) return true;
        return false;
    }
};
```

Anyways, it got trickier and trickier before I finally quit. (Though it did inspire me to figure out a way to find all the root-to-leaf paths).

#### *Sol1: Recursion*

Always treat the tree on a certain level of recursion as a node with two children, both of which are like an unknown cloud.

```C++
bool hasPathSum(TreeNode* root, int targetSum){
    if(!root) return false; // exit
    // tasks within current level: 1. determine whether has matched by looking at current node 2. if fails or else keep looking
    // if is the leaf node
    if(!root->left && !root->right) return root->val == targetSum;
    
    // returns whether or not current node constitutes the path
    return (hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val) );
}
```

#### *Sol2: BFS*

Level-order traversal used to be something I was reluctant to resort to, but now its simplicity in logic has gained my favor

```C++
#include<queue>
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root) return false;
        queue<TreeNode*> trqu;  // 
        queue<int> sums;  // length of path till current node
        trqu.push(root);
        sums.push(root->val);

        while(!trqu.empty()){
            TreeNode* curNode = trqu.front(); trqu.pop();
            int curSum = sums.front(); sums.pop();

            if(!curNode->left && !curNode->right){
                if(curSum == targetSum) return true;
                else continue;  // doesn't work out this path. try out other paths.
            }

            if(curNode->left) {
                trqu.push(curNode->left); sums.push(curNode->left->val + curSum);
            }
            if(curNode->right){
                trqu.push(curNode->right); sums.push(curNode->right->val + curSum);
            }
        }
        return false;
    }
};
```

