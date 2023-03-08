# LeetCode 200

Interlude: An intriguing problem from [Princeton](https://coursera.cs.princeton.edu/algs4/assignments/hello/specification.php)

[TOC]

## Data Structure

### Linked List

#### 160  Intersection of Two Linked Lists (Easy)

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

#### 206 Reverse Linked List (Easy)

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

#### 19 Remove Nth Node From the End of List (Medium)

##### *Sol1: Stack*

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

##### *Sol2: Double pointers*

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

#### 24. Swap Nodes in Pairs (Medium)

##### ***Sol1: Recursion***

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

##### *Sol2: Iteration*

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

#### 445. Add Two Numbers II (Medium)

##### ***Sol1: Reverse the list with recursion***

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

##### *Sol2: Stack*

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

#### 234. Palindrome Linked List (Easy)

##### *Sol1: Stack* 

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

##### *Sol2: find_middle, reverse, and check*

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

#### 725. Split Linked List in Parts(Medium)

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

### Tree

#### [104. Maximum Depth of Binary Tree (Easy)](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

##### *Sol1: BFS*

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

##### *Sol2: DFS*

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

#### 110. Balanced Binary Tree (Easy)

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

#### 543. Diameter of Binary Tree (Easy)

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

#### 226. Invert Binary Tree (Easy)

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

#### 617. Merge Two Binary Trees (Easy)

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

#### 112. Path Sum (Easy)

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

##### *Sol1: Recursion*

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

##### *Sol2: BFS*

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

#### [437. Path Sum III](https://leetcode.cn/problems/path-sum-iii/) (Medium)

##### *Sol1 : Recursion*

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

##### *Sol2: unordered_map + prefix sum*

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

#### [572. Subtree of Another Tree](https://leetcode.cn/problems/subtree-of-another-tree/) (Easy)

##### *Sol1: BF with DFS* 

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

##### *Sol2: String with KMP*

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

##### *Sol3: [Hash](https://leetcode.cn/problems/symmetric-tree/solution/dui-cheng-er-cha-shu-by-leetcode-solution/)*

#### [101. Symmetric Tree](https://leetcode.cn/problems/symmetric-tree/) （Easy）

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

#### [111. Minimum Depth of Binary Tree](https://leetcode.cn/problems/minimum-depth-of-binary-tree/) (Easy)

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

#### [404. Sum of Left Leaves](https://leetcode.cn/problems/sum-of-left-leaves/) (Easy)

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

#### [687. Longest Univalue Path](https://leetcode.cn/problems/longest-univalue-path/) （Medium）

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

#### [337. House Robber III](https://leetcode.cn/problems/house-robber-iii/) (Medium)

##### *Sol1: unordered_map to record*

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

##### *Sol2: State induction*

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

#### [671. Second Minimum Node In a Binary Tree](https://leetcode.cn/problems/second-minimum-node-in-a-binary-tree/) （Easy）

We designate the return value of our recursive function to be the second minimum value that can be found from current node.

```C++
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        // exit
        if(!root || !(root->left || root->right)) return -1;
        
        // key. second minimum val only appears when
        if(root->left && root->right){
            if(root->left->val == root->right->val){
                // if the same, go to child nodes. But remember to judge the positivity of results! otherwise -1 would ususally gets returned.
                int left_m = findSecondMinimumValue(root->left);
                int right_m = findSecondMinimumValue(root->right);
                if(left_m<0) return right_m;
                if(right_m<0) return left_m;
                return min(right_m, left_m);
            } 
            else {
                // if different, do not rush to return. smaller values may appear in under the currently smaller node
                TreeNode* smaller = (root->left->val > root->right->val) ? root->right : root->left;
                TreeNode* bigger = (root->left->val > root->right->val) ? root->left : root->right;
                int smaller_side = findSecondMinimumValue(smaller);
                return (smaller_side>0) ? min(bigger->val, smaller_side) : bigger->val;
            }
        }
        if(root->left) return findSecondMinimumValue(root->left);
        else return findSecondMinimumValue(root->right);

    }
};
```

#### [637. Average of Levels in Binary Tree](https://leetcode.cn/problems/average-of-levels-in-binary-tree/) (Easy)

Using the trick learnt at [104](https://leetcode.com/problems/maximum-depth-of-binary-tree/), we can easily acquire the ins and outs of the nodes on a certain level.

```C++
#include<queue>
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> qu;
        TreeNode* p = root;
        qu.push(p);
        vector<double>v;

        while(!qu.empty()){
            double curNodes = qu.size();
            double sum = 0, cnt = 0;
            while(curNodes>0){
                p = qu.front(); qu.pop();
                if(p->left) qu.push(p->left);
                if(p->right) qu.push(p->right);
                curNodes--;
                cnt++;
                sum += (double) p->val;
            }
            double avg = sum / cnt;
            v.push_back(avg);
        }
        return v;
    }
};
```

#### [513. Find Bottom Left Tree Value](https://leetcode.cn/problems/find-bottom-left-tree-value/) (Medium)

##### *Sol1: trick*

Considering that ordinary level-order traversal does not draw a line between the levels, we still stick to our trick, with a variable maintained.

```C++
#include<queue>
class Solution {
public:
    TreeNode* res;
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> qu;
        TreeNode* p = root;
        qu.push(p);

        while(!qu.empty()){
            int curNum = qu.size();
            int track = curNum;
            while(curNum > 0){
                p = qu.front(); qu.pop();
                if(curNum == track) res = p; // must be the first node of some level

                if(p->left) qu.push(p->left);
                if(p->right) qu.push(p->right);
                curNum--;
            }
        }
        return res->val;
    }
};
```

##### *Sol2: right-to-left level-order traversal*

The leftmost bottom-most node is exactly the last node in a right-to-left level-order traversal:

```C++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        int ret;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            if (p->right) {
                q.push(p->right);
            }
            if (p->left) {
                q.push(p->left);
            }
            ret = p->val;
        }
        return ret;
    }
};
```

#### [1448. Count Good Nodes in Binary Tree](https://leetcode.cn/problems/count-good-nodes-in-binary-tree/) (Medium)

The solution is relatively straightforward. To be able to think of using a variable `max_to_cur`, however, took me several minutes. Here’s a brief picture of my thoughts:

> how do we judge if the child of our current node is a good node?  
>
> - if current node is good:
   - - if child val is smaller: child is not good
     - if child val is greater: child is good
   - if current node is not good:
   - - if child node is smaller: child is not good
     - if is greater: can not be ascertained. need to examine the actual maximum val on the path

```C++
class Solution {
public:
    int judge(TreeNode* r, int max_to_cur){
        // max_to_cur stores the maximum val from root to curNode
        // what to return? total num of good nodes from curNodes
        // what to do? judge if is good node and recursively judge its children 

        bool is_good = false; 
        int new_max = max_to_cur;
        if(r->val >= max_to_cur) {
            is_good = true;
            new_max = r->val;
        }

        int leftgoods = 0, rightgoods = 0;
        if(r->left) leftgoods = judge(r->left, new_max);
        if(r->right) rightgoods =judge(r->right, new_max);

        return leftgoods + rightgoods + is_good;

    }
    int goodNodes(TreeNode* root) {
        return judge(root, root->val);
    }
};
```

### Stacks and Queues

#### [232. Implement Queues using Stacks](https://leetcode.cn/problems/implement-queue-using-stacks/) (Easy)

My initial shot was like this:

```C++
#include<stack>
using namespace std;
class MyQueue {
public:
    stack<int> st1;
    stack<int> st2;
        
    MyQueue() {
    }
    
    void push(int x) {
        st1.push(x);
    }
    
    int pop() {
        int tmp, res;
        while(!st1.empty()){ //dump st1 elements to st2
            res = st1.top(); st1.pop();
            st2.push(res);
        }
        st2.pop();
        while(!st2.empty()){
            tmp = st2.top(); st2.pop();
            st1.push(tmp);
        }
        return res;
    }
    
    int peek() {
        int tmp, res;
        while(!st1.empty()){
            res = st1.top(); st1.pop();
            st2.push(res);
        }
        while(!st2.empty()){
            tmp = st2.top(); st2.pop();
            st1.push(tmp);
        }
        return res;
    }
    
    bool empty() {
        return st1.empty();
    }
};
```

But studying the official solution, we do not have to move the st2 elements back to st1 again every time we do a peek or pop:

- Instack: temporily store some elements that will go to Outstack for peek or pop.
- Outstack: store elements like a queue. Before it is empty, it does not take in new elements.

![image-20230207235239371](C:\Users\Benjamin\AppData\Roaming\Typora\typora-user-images\image-20230207235239371.png)

```C++
class MyQueue {
private:
    stack<int> inStack, outStack;

    void in2out() {
        while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }

public:
    MyQueue() {}

    void push(int x) {
        inStack.push(x);
    }

    int pop() {
        if (outStack.empty()) { // KEY !!!!!!
            // only go to outstack if it's all empty
            in2out();
        }
        int x = outStack.top();
        outStack.pop();
        return x;
    }

    int peek() {
        if (outStack.empty()) {
            in2out();
        }
        return outStack.top();
    }

    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};
```

#### [225. Implement Stack using Queues](https://leetcode.cn/problems/implement-stack-using-queues/) (Easy)

##### *Sol1: Two Queues*

I alternately use this two queues as main queue to store elements. 

To get the element at the tail of the queue, we send all the elements before it into another queue, and use .front to get the element. After this we have an empty queue and a complete queue. Before each pop or top, we need to find out which one is complete so that we can start moving elements off it.

```C++
#include<queue>
using namespace std;
class MyStack {
public:
    queue<int> qu1;
    queue<int> qu2;
    MyStack() {}

    int handle(int opt){ // opt: if 1, needs to pop
        int res;
        if(qu1.empty()){
            while(!qu2.empty()){
                res = qu2.front();
                qu2.pop();

                if(qu2.empty() && opt);
                else qu1.push(res);
            }
        }
        else{
            while(!qu1.empty()){
                res = qu1.front();
                qu1.pop();

                if(qu1.empty() && opt);
                else qu2.push(res);
            }
        }
        return res;
    }
    void push(int x) {
        if(!qu1.empty()) qu1.push(x);
        else qu2.push(x);

    }
    
    int pop() {
        return handle(1);
    }
    
    int top() {
        return handle(0);
    }
    
    bool empty() {
        return qu1.empty() && qu2.empty();
    }
};

```

##### *Sol2: One Queue*

In push, we push the element into the queue, and constantly push-pop elements in the queue till we get the target element. (Imagine waiting in a queue and people in front you quickly getting things done and leaving, in this case you can get to the front quite soon.) 

```C++
class MyStack {
public:
    queue<int> q;
    /** Initialize your data structure here. */
    MyStack() {}
    
    /** Push element x onto stack. */
    void push(int x) {
        int n = q.size();
        q.push(x);
        for (int i = 0; i < n; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int r = q.front();
        q.pop();
        return r;
    }
    
    /** Get the top element. */
    int top() {
        int r = q.front();
        return r;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }
};
```

#### [739. Daily Temperatures](https://leetcode.cn/problems/daily-temperatures/) （Medium）

**Monotonic Stack** : *a stack in which the elements are in increasing or decreasing order from the bottom to the top of the stack.* 

This is a good model we can resort to whenever we run into problems related to the first minimum/ maximum elements from a certain element.

```C++
#include<stack>
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> indices;  //store the indices of temps
        int itr, len = temperatures.size();
        indices.push(0);
        vector<int> ans(len);
        for(itr = 0; itr < len ; ++itr){ // examine elements one by one
            int curHighInd = indices.top();
            // found a higher temperature, process all previous remaining ones that are lower than it 
            while(!indices.empty() && temperatures[itr] > temperatures[curHighInd]){
                ans[curHighInd] = itr - curHighInd;
                indices.pop();
                if(!indices.empty()) curHighInd = indices.top();
            }
            // after processing, store the index
            indices.push(itr);
        }
        return ans;
    }
};
```

#### [503. Next Greater Element II](https://leetcode.cn/problems/next-greater-element-ii/) （Medium）

Taking the similar strategy to the previous problem, the solution should be straightforward:

```C++
#include<stack>
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> indices;
        indices.push(0);
        int len = nums.size(), i;
        vector<int> ans(len, -1);
        for(i = 1; i < 2*len - 1 ; i++){
            // choosing 2*len -1 ensures that the loop ends right before each element is visited again, thus obviateing the need for another visited array.
            while(!indices.empty() && nums[i % len] > nums[indices.top()]){ // found a greater number
                int got = indices.top(); // id of previous greater one
                indices.pop();
                ans[got] = nums[i%len];
            }
            indices.push(i%len);
        }
        return ans;
    }
};
```

### Graph

#### [207. Course Schedule](https://leetcode.cn/problems/course-schedule/) (Medium)

My solution is rather lumbersome and ponderous:

```C++
#include<queue>
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // pair [0,1] means that course 0 relies on course 1
        int relies = prerequisites.size(); // num of relies
        vector<int>dependent(numCourses,0); 
        vector<vector<int>> g(numCourses,vector<int>(numCourses,0));
        queue<int> indie;
        for(int i = 0; i < relies; i++){
           g[prerequisites[i][0]][prerequisites[i][1]] = 1;
           dependent[prerequisites[i][0]]++;
        }
        for(int i = 0; i < numCourses; i++){
           if(!dependent[i]) {
               indie.push(i);
               dependent[i] = -1; // visited
           }
        }

        while(!indie.empty()){         
           int curNode = indie.front(); indie.pop();
           // decrement the out ind of nodes reliant on curNode
           for(int j = 0; j < numCourses; j++){
               if(g[j][curNode]){ // if reliant
                   g[j][curNode]--;
                   dependent[j]--;
               } 
            }
            for(int i = 0; i < numCourses; i++)  // again find all indies
                if(!dependent[i] && dependent[i] != -1) {
                    indie.push(i);
                    dependent[i] = -1;
                }   
        }
        for(int i = 0; i < numCourses; i++)
            if(dependent[i] != -1) return false;
        return true; 
    }
};
```

The [official solution](https://leetcode.cn/problems/course-schedule/solution/ke-cheng-biao-by-leetcode-solution/) offers another perspective on topological sorting:

```C++
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited;
    bool valid = true;

public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v: edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
    }
};
```

#### [785. Is Graph Bipartite?](https://leetcode.cn/problems/is-graph-bipartite/)  (Medium)

My initial solution was like this:

```C++
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // coloring nodes
        int nodes = graph.size();
        // if(nodes % 2 == 1) return false;
        vector<int> color(nodes, 0);
        color[0] = 1; // color the 1st one black

        for(int i = 0; i<nodes ;i++){
            int numOfAdj = graph[i].size();  
            for(int j = 0; j< numOfAdj; j++){ 
                if(color[graph[i][j]]==0){   
                    if(color[i]==1) color[graph[i][j]] = 2;
                    else color[graph[i][j]] = 1;
                }
                else{
                    if(color[graph[i][j]] == color[i]) return false;
                }
            }
        }
        return true;
    }
};
```

It worked until I ran into some large samples. However, that’s not where the problem really lies.

```C++
class Solution {
public:
    const int UNCOLORED = 0;
    const int RED = 1;
    const int GREEN = 2;
    vector<int>color;
    bool flag;

    void dfs(vector<vector<int>>& g, int v, int tocol){ // 给当前结点上色，并判断所有相邻的

                color[v] = tocol;
        int cNei = (tocol == RED ? GREEN : RED);
        for (int neighbor: g[v]) {
            if (color[neighbor] == UNCOLORED) {
                dfs(g,neighbor, cNei);
                if (!flag) {
                    return;
                }
            }
            else if (color[neighbor] != cNei) {
                flag = false;
                return;
            }
        }
     
    }
    bool isBipartite(vector<vector<int>>& graph) {
       
        int n = graph.size();
        flag = true;
        color.assign(n, UNCOLORED);
        for (int i = 0; i < n && flag; ++i) {
            if (color[i] == UNCOLORED) {
                dfs(graph,i, RED);
            }
        }
        return flag;
    }
};
```

#### [127. Word Ladder](https://leetcode.cn/problems/word-ladder/) (Hard)

My initial code:

```C++
#include<queue>
#include <vector>
#include <algorithm>
class Solution {
public:
    
    bool isAdjacent(string s, string t){
        int len = s.length(); if(len != t.length()) return false;
        int dif = 0;
        for(int i = 0; i < len; i++)
            if(s[i]!=t[i]){
                switch (dif){
                    case 0: dif++; break; // 这是第一次不一样，加一
                    case 1: return false; // 这是第二次不一样，直接返回
                }
            }
        return dif==1;
    }
    vector<vector<int>> createAdj(vector<string>& wordList){
        // 每个 word 都是等长的
        int num = wordList.size(), len = wordList[0].length();
        vector<vector<int>> adj(num, vector<int>(num, -1));
        for(int i = 0; i < num; i++){
            for(int j = 0; j < num; j++){
                if(i!=j && (adj[i][j] == -1)) { // 没访问过
                    if(isAdjacent(wordList[i], wordList[j])) adj[i][j] = adj[j][i] = 1;
                    else adj[i][j] = adj[j][i] = 0;
                }
            }
        }
        return adj;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        vector<string> wl = wordList;

        std::vector<int>::iterator it;
        it = std::find(wl.begin(),wl.end(), endWord);
        if(it == wl.end()) return 0;

        int endInd = it - wl.begin(), beginInd, len;
        it = std::find(wl.begin(),wl.end(), beginWord);

        if(it == wl.end()){
            wl.push_back(beginWord);
            num = wl.size();
            beginInd = len - 1;
        }
        else{
            num = wl.size();
            beginInd = it - wl.begin();
        }

        // 准备工作，获得了 图中 beginInd, endInd 的编号
        vector<vector<int>> AdjG = createAdj(wl);

        queue<int> ads;
        ads.push(beginInd);

        int ans = 0;
        while(!ads.empty()){
            int n = ads.size();
            for(int i = 0 ; i<n; i++){
                int curNode = ads.front(); ads.pop();
                if(curNode == endInd) return ans;
                for(int j = 0; j<n ; j++){
                    if(AdjG[i][j] == 1){
                        AdjG[i][j] = 2; // visited
                        ads.push(j);
                    }
                }
            }
            ans++;
        }
        return 0;

    }
};
```

### Heap

#### [215. Kth Largest Element in an Array](https://leetcode.cn/problems/kth-largest-element-in-an-array/) (Medium)

I directly used priority_queue in C++ as my heap. Should’ve written one myself but I’m busy preparing for my final these days.

```C++
#include<queue>
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> bh;
        for(auto i : nums){
            bh.push(i);
        }
        for(int i = 0; i < k - 1; i++) bh.pop();
        return bh.top();
    }
};
```

### Search

#### [33. Search in Rotated Sorted Array](https://leetcode.cn/problems/search-in-rotated-sorted-array/)(Medium)

The problem requires a solution of time complexity $O(log_2n)$, which I had a rough idea but failed to find out what was wrong with my implementation. This is a straightforward solution:

In a word, we split the array by into two halves and one of them must be in ascending order. Apply binary search on the ordered half and split the unordered half into halves again:

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = (int)nums.size();
        if (!n) {
            return -1;
        }
        if (n == 1) {
            return nums[0] == target ? 0 : -1;
        }
        int l = 0, r = n - 1;
        while (l <= r) {
       
            int mid = (l + r) / 2;
            if (nums[mid] == target) return mid;
            if (nums[l] <= nums[mid]) {
                // if the left half is in order
                if (nums[l] <= target && target < nums[mid]) {
                    // if the target is in the left half
                    r = mid - 1;
                } else {
                    // else the target can be in the right half
                    l = mid + 1;
                }
            } 
            else {
                // if the left half is out of order
                if (nums[mid] < target && target <= nums[r]) {
                    // if the answer is in the right half
                    l = mid + 1;
                } else {
                    // then the answer can be in the left half
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};
```



> Interlude: hasn't updated in days and will so until next week when the exams are over. Just had my data structure test today and ... although i messed up the multiple choices part where i didn't even review sparse matrices and balanced binary tree, all these leetcode problems did help me solve the algorithm problems smoothly. Funny thing is that although i have seen better solutions on leetcode, i still could only think of my initial "low efficiency" poor solutions (which will also do though). I guess some review is due after a certain while!

### Hash Map

As I have little knowledge of hash maps in C++, I’ve searched up some key takeaways for reference:

> Hash_map in C++: implemented using `unordered_map`, and here is some working knowledge of it:
>
> - create a hash map: `unordered_map<int,int> m;` 
>
> - add pairs: 
>
>   - .insert() : m.insert(pait<type_a>, <type_b>(1, 10))
>   - directly add using array notation: m[key] = value
>
> - find and count:
>
>   - `if(m.find(key) != m.end()) return m[key];`
>   - `return m.count(3);`
>
> - size and empty:
>
>   - `m.size()`
>   - `m.clear()`
>
> - traversal:
>
>   - ```C++
>     for (auto p : count) {
>     	int front = p.first;   //key
>         int end = p.second;   //value
>     }
>     ```
>
>   - ```C++
>     for(auto it=m.begin();it!=m.end();it++)
>     {
>         int front = it->first;   //key
>         int end = it->second;   //value
>     }
>     ```
>

#### [217. Contains Duplicate](https://leetcode.cn/problems/contains-duplicate/)

```C++
#include<set>
using namespace std;
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set<int> s;
        for(auto i : nums) s.insert(i);
        return !(nums.size()==s.size());
    }
};
```

### Dynamic Planning & Greed

#### [455. Assign Cookies](https://leetcode.cn/problems/assign-cookies/) (Easy)

We attempt to satisfy child with the least appetite first, and then go up seeing how many we can satisfy at most.

```C++
#include<algorithm>
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if(!s.size())return 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int appet_num = g.size(), cookie_num = s.size();

        int app = 0,coo = 0; // two iterators
        while(app < appet_num && coo < cookie_num){
            if(s[coo] >= g[app]){
                app++; coo++;
            }
            else{
                coo++;
            }
        }
        return app++;
    }
};
```

#### [121. Best Time to Buy and Sell Stock](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/) (Easy)

Here’s a clever way to consider this problem: assume we are the one trading stocks in the case, except that we never sell but observe. On the i-th day, we have already acquired data on the previous i-1-th day, which means we have known the lowest price to date and the maximum profits we earn to date. On the i-th day, we again acquire that day’s price and update our lowest price to date, and thus updating our maximum profits to date, so that we always stay updated of the maximum profits we have had the chance to earn in the first i days (we can’t actually earn because we only observe!) 

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size(); if(len == 1) return 0;

        int min_to_date = prices[0], max_pro = 0;
        for(int i = 1; i< len; i++){
            min_to_date = min_to_date < prices[i] ? min_to_date : prices[i];
            max_pro = max_pro > (prices[i] - min_to_date) ? max_pro : (prices[i] - min_to_date);
        }
        return max_pro;
    }
};
```

#### [122. Best Time to Buy and Sell Stock II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/) (Medium)

This one is different, yet not necessarily harder. After some thoughts we come to the conclusion that: the most profitable strategy is to sell the stocks once we observe a rise.

In every loop there happen two cases：

1. transaction happens. if today’s price is higher, we sell our stocks. And we **postulate** today’s price is the lowest price from now on. Record this price with `last`.
2. transaction doesn’t happen. if today’s price is not higher, we do not sell our stocks. Note that we have formed a guess of the recent lowest price before today. So we **update** this guess by modifying `last`. (Modification of our guess does not mean that we PURCHASE the stocks.)

Note that **it is only when we decide to sell our stocks that we actually purchase the “last stocks”**. This may border on the wisdom of hindsight but is a common strategy of dynamic planning.

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        int last = prices[0], pro = 0;
        for(int i = 1; i < len ; i++){
            if(prices[i]>last){  // today's price is higher, sell immediately
                pro += prices[i] - last;
                last = prices[i]; // can buy the stocks on the same day
            }
            else last = prices[i]; // today's price is lower. modify our guess and conjecture that today's price is the recent lowest
        }
        return pro;
    } 
};
```

#### [435. Non-overlapping Intervals](https://leetcode.cn/problems/non-overlapping-intervals/) (Medium)

I did not work this one out. My original plan was to sort the vectors based on their left limits, and use the right limit as a second key (like radix sort), but I did not implement it.

In fact, the solution gives a smarter perspective, which only sorts the array with a single key:

- sort the array in ascending order with the key being the right border
- those with the smallest right border are equivalent in this problem, since the left border of the first interval does not matter. Therefore, we randomly pick one (the first one)
- then go right until we find one whose left border are greater than the last one’s right border. This means that we have found another interval to be added. Keep doing so and we can acquire the intervals that make the final list.

```C++
 
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v) {
            return u[1] < v[1];
        });

        int n = intervals.size();
        int right = intervals[0][1];
        int ans = 1;
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] >= right) {
                ++ans;
                right = intervals[i][1];
            }
        }
        return n - ans;
    }
```

> Note that vector comes with a comparison function itself. We can also write our own comparator function and pass it as a third parameter. The comparator function checks, if the statement returned, is true or false and returns a bool value which is passed to the sort function.
>
> ```C++
> struct Interval {
>     int start, end;
> };
> bool compareInterval(Interval i1, Interval i2)
> {
>     return (i1.start < i2.start);
> }
> 
> vector<Interval> v { { 6, 8 }, { 1, 9 }, { 2, 4 }, { 4, 7 } };
> sort(v.begin(), v.end(), compareInterval);
> ```

#### [452. Minimum Number of Arrows to Burst Balloons](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/) （Medium）

Borrowing what we have learnt from the last problem, we can quickly come to a solution here.

```C++
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int len = points.size();
        if(len == 1) return 1;
        
        sort(points.begin(), points.end(), [](const auto& u, const auto& v) {
            return u[1] < v[1];
        });
        int curRight = points[0][1], ans = 1;
        for(int i = 1; i < len; i++){ 
            if(points[i][0] <= curRight) continue; 
            curRight = points[i][1];
            ans ++;
        }
        return ans;
    }
};
```

> Also, I had in mind this state transiton plan that goes like:
>
> - assume that f[i] represents the number of arrows needed to burst all balloons before and incl the i-th one.
> - if none of the left bounds of the next set of balloons are greater than current right bound, then $f[i] = f[i-1] + 1$
> - else $f[i] = f[i-1]$   

#### [406. Queue Reconstruction by Height](https://leetcode.cn/problems/queue-reconstruction-by-height/) (Medium)

This is an intriguing problem.

At first I was somewhat misled by the hint, and had been considering how shall we arrange for the shortest people and then the taller people. Not that it’s wrong, but after thinking backwards everything clicks so quickly ---- that is, we consider **arranging for the tallest people first**.

Say we consider the tallest person. Then he must be at the very front of the queue since there can be no one taller than him (so his person[1] == 0). Moving on to the second tallest person. **We know for sure that there can only be two cases as to his person[1] : 1 or 0**. This gives us an important insight:

**The tallest person doesn’t care about his position in the queue**. In broader terms, a person only has to consider the relative positions of himself and of those who are taller than him. This leads us to **INSERT** persons into the queue, starting from the tallest.

```C++
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int len = people.size();  
        if(len == 1) return people;

        vector<vector<int>>qu;     
        // sort from tallest to shortest, while putting those with a smaller pos number closer to front
        sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]);
        });
        for(auto person : people){
            qu.insert(qu.begin() + person[1], person);
        }
        return qu;    
    }
};
```

#### [605. Can Place Flowers](https://leetcode.cn/problems/can-place-flowers/) （Easy）

```C++
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len = flowerbed.size(); 
        
        for(int i = 0; i< len; i++){
            
            if(flowerbed[i] == 1){
                i++;
                continue;
            }
            else if(flowerbed[i] == 0){ 
                if(i+1<len && flowerbed[i+1] == 0) {
                    n--;
                    i++;
                    continue;
                }
                else if(i + 1 < len && flowerbed[i+1]== 1){
                    i = i+2;
                    continue;
                }
                else if(i + 1 >= len){
                    n-- ; continue;
                }
            }
        }
        return n<=0;
    }
};
```

#### [392. Is Subsequence](https://leetcode.cn/problems/is-subsequence/) （Easy）

```C++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int lens = s.length(), lent = t.length();
        if(lens > lent) return false;
        if(lent == 0) return lens == 0;
        if(lens == 0) return true;

        char target = s[0];
        int j = 0;

        for(int i = 0; i < lent; i++){
            if(t[i] == target){
                if(j == lens - 1) return true;
                else{
                    j++;
                    target = s[j];
                }
            }
        }
        return false;
    }
};
```

#### [665. Non-decreasing Array](https://leetcode.cn/problems/non-decreasing-array/) （Medium）

Like many others, I naively wrote this at the first sight only to be ruthlessly failed:

```python
class Solution(object):
    def checkPossibility(self, nums):
        count = 0
        N = len(nums)
        for i in range(N):
            if i > 0 and nums[i] < nums[i - 1]:
                count += 1
        return count <= 1
```

I shall not pinpoint where this goes wrong. But here’s the correct logic: **Greedy**. We are explorers exploring along the vector. We only know info about those elements we have traversed and have no idea of those we haven’t. Therefore, we gotta be super **cautious**:

- We don’t want to set any element bigger, because that will make it harder for following elements to be non-decreasing.
- So every time we encounter a *drop*, we always tend to set the left one smaller to fit the non-decreasing pattern rather than set the right one greater.
- However, there are cases where we have no option but to set the right one greater:
  - There is no left one. i.e, i == 0;
  - the prior elements are already bigger than the right one. 
- Excluding these cases, we finish our exploration

```C++
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int len = nums.size();
        if(len <= 2) return true;
        int modify = 0;
        for(int i = 0; i< len-1; i++){
            // traverse the vector
            if(nums[i] > nums[i+1]){
                // a drop happens
                if(i == 0) {
                    nums[i] = nums[i+1];
                    modify++;
                    continue;
                }    
                
                int pre = nums[i-1];
                if(pre > nums[i+1]){
                    nums[i+1] = nums[i];
                    modify++;
                }
                else{
                    nums[i] = nums[i+1];
                    modify++;
                }
            }
            
        }
        return modify<=1;
         
    }
};
```

#### [53. Maximum Subarray](https://leetcode.cn/problems/maximum-subarray/) (Medium)

> similar problems: 300 、152 

This is a very classic problem. Apparently we would have to resort to dynamic planning but there’s just this very tricky uncertainty. However, by defining such uncertainty ourselves, the problem may be appear less formidable:

- We are uncertain **what number is gonna make it into our final subarray**  ----> then we can get the maximum sum of all the subarrays that go through a certain element
- However, we are uncertain **where our selected number is gonna be** in the subarray. ----> then we define our goal as to get the maximum subarray **ending with the element**.

**Note that for every element, we explicitly requires it to be in the subarray.**

```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if(len <= 1) return nums[0]; 
        vector<int> dp(len); // the arrays ending with nums[i] with the largest sum
        dp[0] = nums[0];
        for(int i = 1; i < len; i++){
            if(dp[i-1]>0) dp[i] = dp[i-1]+nums[i];
            else dp[i] = nums[i];
        } 

        int max = dp[0];
        for(auto i : dp)
            max = max > i ? max : i;
        return max;

    }
};
```

#### [763. Partition Labels](https://leetcode.cn/problems/partition-labels/) （Medium）

Havent thoroughly figured this one out. Will revisits sometime later.

```C++
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26];
        int length = s.size();
        for (int i = 0; i < length; i++) {
            last[s[i] - 'a'] = i;
        }
        vector<int> partition;
        int start = 0, end = 0;
        for (int i = 0; i < length; i++) {
            end = max(end, last[s[i] - 'a']);
            if (i == end) {
                partition.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return partition;
    }
};

```

#### [300. Longest Increasing Subsequence](https://leetcode.cn/problems/longest-increasing-subsequence/) （Medium）

##### *Sol1: DP*

Following [53. Maximum Subarray](https://leetcode.cn/problems/maximum-subarray/) , this one should’t be hard.

```C++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // attempt 1: start, end, longest: FAILED, misread what substr means
        // attempt 2: dp, use LoInSub[] to represent the length of longest increasing subsequence ending with i
        int len = nums.size();
        if(len == 1) return 1;
        vector<int> LoInSub(len, 1);
        for(int i = 1; i < len; i++){
            int tmp = LoInSub[i];
            for(int j = 1; j <= i; j++){
                if(nums[i] > nums[i-j]){
                    tmp = tmp > LoInSub[i-j] + 1 ? tmp : (LoInSub[i-j] + 1);
                }
            }
            LoInSub[i] = tmp;
        }
        int maxi =LoInSub[0];
        for(auto i : LoInSub){
            maxi = maxi > i ? maxi : i;
        }
        return maxi;
    }
};
```

##### *Sol2: Greed + DP*

Another more advanced solution: 

- let an array tails such that tails[i] is the element at the tail of a subarray of length i; then tails[i] must be increasing.
- iterate over nums:
  - if nums[i] > tails end element, append it to tails
  - else, replace the smallest element in tails that is bigger than nums[i] with nums[i]

```C++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = (int)nums.size();
        if (n == 0) {
            return 0;
        }
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) {
                d[++len] = nums[i];
            } else {
                int l = 1, r = len, pos = 0; 
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};
```

