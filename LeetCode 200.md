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

### [437. Path Sum III](https://leetcode.cn/problems/path-sum-iii/) (Medium)

#### *Sol1 : Recursion*

> The fact that leetcode went so far as to devise a ridiculously big input just to fail my code is abhorrent. I finally got past the test when I changed the type into `long long` after an hour of struggling.

We use rootSum to count the qualified paths that starts from a root node, and in pathSum we treat every node as a root node.

```C++
class Solution {
public:
    long long rootSum(TreeNode* root, long long targetSum) {
        if (!root) return 0;
        return rootSum(root->left, targetSum - root->val) + rootSum(root->right, targetSum - root->val) +  (root->val == targetSum);
    }

    int pathSum(TreeNode* root, long long targetSum) {
        if (!root) return 0;
        long long ret = rootSum(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
        return ret;
    }
};
```

#### *Sol2: unordered_map + prefix sum*

It's my first time using `unordered_map` so I've collected some references to the usage.

> Like `map`, `unordered_map` can also be used as a dictionary, but `map` is implemented through Red-black tree, which makes all elements within it ordered, while `unordered_map` is implemented on hash, which lowers the time complexity and the elements are unordered.

```C++
/*This is only some reference*/

#include<string>  
#include<unordered_map>
using namespace std; 
unordered_map<string, int>  dict; // declaration

// Three ways to insert data
dict.insert(pair<string,int>("apple",2));
dict.insert(unordered_map<string, int>::value_type("orange",3));
dict["banana"] = 6;

cout<<dict.empty()<<endl;  // if it is empty

// iteration
unordered_map<string, int>::iterator iter;
for(iter=dict.begin();iter!=dict.end();iter++)
	cout<<iter->first<<ends<<iter->second<<endl; // first points to key and second points to value

// use iterator to search
if((iter=dict.find("banana"))!=dict.end())
	cout<<"banana="<<iter->second<<endl;
else
	cout<<"can't find it!"<<endl;
```

And the solution:

```C++
class Solution {
public:
    unordered_map<long long, int> prefix;   //< prefix_Sum, how_many_times_we_have_ this_prefix_sum>

    int dfs(TreeNode *root, long long curr, int targetSum) {
        if (!root) {
            return 0;
        }

        int ret = 0;
        curr += root->val;   // update current sum
        if (prefix.count(curr - targetSum)) {
            // if there exists a prefix sum that is curr - targetSum, then there exists a pathsum equal to targetSum
            ret = prefix[curr - targetSum];  // number of pathsums equal to targetSum
        }

        prefix[curr]++;  // update the dictionary
        ret += dfs(root->left, curr, targetSum);   // find all downstream paths
        ret += dfs(root->right, curr, targetSum);
        prefix[curr]--;  // restore the dictionary, bc we are looking for other nodes

        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        prefix[0] = 1; // there is only a single path whose prefix sum is 0: not_a_path
        return dfs(root, 0, targetSum);
    }
};
```

By Feb 4th I haven't thoroughly grasped this usage. We'll see in the future.

### [572. Subtree of Another Tree](https://leetcode.cn/problems/subtree-of-another-tree/) (Easy)

#### *Sol1: BF with DFS* 

This was all I had with me when I was doing it.

```C++
class Solution {
public:
    bool isSame(TreeNode* root, TreeNode* subRoot){
        if(!root && !subRoot) return true;  // both null, true
        if(!root || !subRoot) return false; // one null the other not, false
        // neither null, judge
        return (root->val == subRoot->val) && isSame(root->left, subRoot->left) && isSame(root->right, subRoot->right);
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(!root && !subRoot) return true;  // both null, true
        if(!root || !subRoot) return false; // one null the other not, false
        return isSame(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};
```

#### *Sol2: String with KMP*

> Property of pre-order traversal: the nodes in a child tree are contiguous as they are in the original tree

To determine whether a tree contains another as a subtree, we only have to serialize both into s and t respectively, and determine whether t is a part of s ! That's where KMP comes in. But this does not make it right, bc if a node has a children while the substree doesn't, it still does not count as a subtree. To overcome this, we add a unique number to all leaf node in the sequentialized string.

```C++
/*This solution is buggy. It fails at sample input No.180*/
#include <vector>
using namespace std;
class Solution {
public:
    const int null1 = 10001, null2 = 10002;
    void getSequence(TreeNode* r, vector<int>& str){
        if(r){
            str.push_back(r->val);
            if(!r->left) str.push_back(null1);else getSequence(r->left, str);
            if(!r->right) str.push_back(null2); else getSequence(r->right, str);
        }
    }
    void getNext(vector<int>& t, int* next){
        int j = 0, k = -1, len = t.size();

        next[0] = -1;

        while(j < len - 1){
            if(k == -1 || next[j] == next[k]){
                k++; j++; next[j] = k;
            }
            else k = next[k];
        }
    }

    int KMP(vector<int>& s, vector<int>& t){
        int n=s.size(),m=t.size();
        int * next = new int[m];
        getNext(t,next);
        int i=0,j=0;
        while(i<n && j<m){
        if(j==-1 || s[i]==t[j]){
            i++;j++;
        }
        else j=next[j];
        }
        if(j>=m) return i-m;
        else return -1;
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        vector<int> s; vector<int> t;
        getSequence(root, s);
        getSequence(subRoot, t);

        return KMP(s, t)>=0;
    }
};
```

#### *Sol3: [Hash](https://leetcode.cn/problems/symmetric-tree/solution/dui-cheng-er-cha-shu-by-leetcode-solution/)*

### [101. Symmetric Tree](https://leetcode.cn/problems/symmetric-tree/) （Easy）

This one is relatively more of a no-brainer compared with others.

```C++
class Solution {
public:
    bool dsf(TreeNode* l, TreeNode* r){
        if(l && r){
            return (l->val == r->val) && dsf(l->left, r->right) && dsf(l->right, r->left);
        }
        else if(!l && !r) return true;
        else return false;
    }
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return dsf(root->left, root->right);
    }
};
```

### [111. Minimum Depth of Binary Tree](https://leetcode.cn/problems/minimum-depth-of-binary-tree/) (Easy)

Easy as it seems, this one got a pitfall that I walked right into. Its definition of a leaf node is a node that has no children, which means a node that only has one does not count.

```C++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        if(!root->left && !root->right) return 1;  // hits a leaf
        if(root->left && root->right)  // both
            return 1+ min(minDepth(root->left), minDepth(root->right));
        if(root->left) return 1+ minDepth(root->left);
        else return 1+ minDepth(root->right);
    }
};
```

### [404. Sum of Left Leaves](https://leetcode.cn/problems/sum-of-left-leaves/) (Easy)

Note that according to the definition, a single node does not count as a left leaf bc it is no left child of others.

```C++
class Solution {
public:
    // according to the definition, a single node does not count as a left leaf
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root) return 0;
        int gain = 0;  // the gain of next level
        // gain only if when curNode has a left child that has no children
        if(root->left && !root->left->left && !root->left->right) 
            gain = root->left->val;
        // Otherwise: has a left node but which has children
        return gain + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right); 
    }
};
```

### [687. Longest Univalue Path](https://leetcode.cn/problems/longest-univalue-path/) （Medium）

My initial idea of this one was flawed. Like [Diameter](https://leetcode.com/problems/diameter-of-binary-tree/), I simply focused on getting the path through a certain node and then iterating all over the tree, and the path length is a sum of its left subtree and right subtree. Therefore, I set the return value of my function lupr to be the longest univalue path running ***through*** the root, not ***from*** the root.

```C++
/*---------WRONG CODE---------*/
class Solution {
public:
    int maxpath;
    int lupr(TreeNode* r){ // longest univalue path from the root
        if(!r) return 0;
        int left_lupr = 0, right_lupr = 0;
        if(r->left && r->left->val == r->val) left_lupr = 1 + lupr(r->left);
        if(r->right && r->right->val == r->val) right_lupr = 1 + lupr(r->right);
        // with no child, 0
        maxpath = max(maxpath, left_lupr +right_lupr);
        return left_lupr + right_lupr ;
    }
    int longestUnivaluePath(TreeNode* root) {
        if(!root) return 0;
        //return lupr(root);
        return max(lupr(root), max(longestUnivaluePath(root->left), longestUnivaluePath(root->right)));
    }
};
```

But this is wrong. Imagine on the next level, to acquire the longest univalue path, we keep on looking, not for another path that ***splits at*** (runs through) the node, but ***stems from*** the node, because that's how we form an undiverging path. So we should designate the return value of that function to be the length of the longest path from the root. 

But how do we calculate the longest path that runs through current node? Take the sum. We maintain a shared variable to keep track of the longest path to date. 

Another problem with the code is that it fails to zero when mismatch happens. When we hit a different-value node, we should immediately set the path length to zero and start over.

```C++
class Solution {
public:
    int maxpath;
    int lupr(TreeNode* r){ // longest univalue path from the root
    // returns a the length of the longest one-side path stemming from current node that has the same value with current node 
        if(!r) return 0;
        
        // must keep recursion, bc the children nodes may contain longer paths.
        // left_lupr is the longest path univalue till r->left
        int left_lupr = lupr(r->left), right_lupr = lupr(r->right);
        
        if(r->left) {
            if(r->left->val == r->val)left_lupr ++;
            else left_lupr = 0;  // if different, zero
        }
        if(r->right) { 
            if(r->right->val == r->val) right_lupr ++;
            else right_lupr = 0;
        }
        
        maxpath = max(maxpath, left_lupr + right_lupr);
        return max(left_lupr, right_lupr) ;
    }
    int longestUnivaluePath(TreeNode* root) {
        if(!root) return 0;
        maxpath = 0;
        lupr(root);
        return maxpath;
    }
};
```

TBH, I cannot guarantee that [today](2023-2-5) I have fully grasped this one. I'll definitely revisit it some day.

> funny enough just when i thought i was heading somewhere with recursion, i hit this one... hope i really get better at it...

### [337. House Robber III](https://leetcode.cn/problems/house-robber-iii/) (Medium)

#### *Sol1: unordered_map to record*

This solution exceeded the time limit.

```C++
/*----------Buggy Code----------*/
class Solution {
public:
    int rob(TreeNode* root) {
        // exit
        if(!root) return 0;
        // task within this level: evaluate the two methods
        int method1 = rob(root->left) + rob(root->right);
        int method2 = root->val;
        if(root->left) method2 += rob(root->left->left) + rob(root->left->right);
        if(root->right) method2 += rob(root->right->left) + rob(root->right->right);
        // return the most money that can be earned if robbing current node
        return max(method1, method2);
    }
};
```

Actually, by the time we reach the return value, we have already computed the most money taht can be earned for this Node. If we adopt an unordered_map to save it, a lot of time and space can be saved.

```C++
#include<unordered_map>
using namespace std;
class Solution {
public:
    unordered_map<TreeNode*, int> record;
    int rob(TreeNode* root) {
        if(!root) return 0;
        
        if(record.find(root)!= record.end()) return record[root];
        
        int method1 = rob(root->left) + rob(root->right);
        int method2 = root->val;
        if(root->left) method2 += rob(root->left->left) + rob(root->left->right);
        if(root->right) method2 += rob(root->right->left) + rob(root->right->right);
        
        record[root] = max(method1, method2);
        
        return max(method1, method2);
    }
};
```

Now this solution does not cause a stack overflow.

#### *Sol2: State induction*

For every node, there exist two states: to rob and to not rob, which we represent with an array int [2]. 

- To not rob, the earnings from this node are the earnings from its two children node **in all cases**.
- To rob, the earnings from this node are the earnings from itself plus those from its its children **when to not rob**.

$$
node[0] = max(rob(node.left)[0], rob(node.left)[1]) + max(rob(node.right)[0] + node.right[1])
$$

$$
node[1] = rob(node.left)[0] + rob(node.right)[0] + node->val
$$

```C++
class Solution {
public:
    int* helper(TreeNode* r){
        // return the earnings respectively of when to rob and when to not rob 
        if(!r) {
            int* tmp = new int[2];
            tmp[0]=0; tmp[1] = 0;
            return tmp;
        }
        int* curEarn = new int[2];
        int* left_arr = helper(r->left);
        int* right_arr = helper(r->right);
        curEarn[0] = max(left_arr[0] , left_arr[1]) + max(right_arr[0] , right_arr[1]);
        curEarn[1] = left_arr[0] + right_arr[0] + r->val;
        return curEarn;
    }
    int rob(TreeNode* root) {
        int* states = helper(root);
        return max(states[0], states[1]);
    }
};
```

