# Binary Trees
* Binary tree has intrinsic order, which is its traversal order: every node in the left subtree comes before root node; every node in the right subtree comes after root node.
```C++
traversal(tree):
    if not tree: return
    traversal(tree.left)
    output tree.item
    traversal(tree.right)
```

|Tree operations:|Implementations:|Complexity:|
|---|---|---
|first_in_tree(node)|go to leftmost node|O(h)
|last_in_tree(node)|go to rightmost node|O(h) 
|successor(node)|return first_in_tree(node.right) if node.right exists else go up the tree until first left branch $^{(1)}$|O(h)
|predecessor(node)|similar as successor(node) $^{(1)}$|O(h)
|insert_after(node,new)|put new at node.right if not node.right else put new at successor(node).left $^{(2)}$|O(h)
|insert_before(node,new)|similar as insert_after(node)|O(h)
|subtree_delete(node)|detach node if node is leaf else iteratively swap node with predecessor(node) if node.left else swap node with successor(node) until node is leaf and detach $^{(3)}$|O(h)

(1)
```C++
successor(node):
    if node.right:
        return first_in_tree(node.right)
    while node.parent and node.parent.left != node:
        node = node.parent
    if node.parent:
        output "find successor!"
    else:
        output "sucessor not exist!"
    return node.parent

predecessor(node):
    if node.left:
        return last_in_tree(node.left)
    p = node.parent
    while p and p.left == x:
        x = p
        p = x.parent
    return p
```
(2)
```C++
insert_after(node,x):
    if not node.right:
        put x at node.right
    else:
        put x at successor(node).left
```
(3)
```C++
subtree_delete(node):
    while not is_leaf(node):
        if node.left:
            swap(node.item, predecessor(node).item)
            node = predecessor(node)
        else:
            swap(node.item, successor(node).item)
            node = successor(node)
    p = node.parent
    detach node
    return p
```

### Binary Tree Sequence and Binary Tree Set Interface
* use tree to implement sequence interface: traversal order = sequence order
* use tree to implement set interface: traversal order = increasing key order of set (BST property).

|Binary Tree Set Operations:|Implementations:|Complexity:
|---|---|---
|subtree_find(node,k)|binary search $^{(4)}$|O(h)
|find_prev(k)|search for k in tree, return previous node if successful else compare with node where search fell off the tree $^{(5)}$|O(h)
|find_next(k)|similar as find_prev(k)|O(h)
|insert(x)|search for x.key in tree, update node if successful else put x at where search fell off the tree $^{(6)}$|O(h)

(4)
```C++
subtree_find(node,k):
    last_compared = node
    while node:
        if node.item == k:
            output "find key!"
            return true, node
        last_compared = node
        if node.item < k:
            node = node.right
        else:
            node = node.left
    output "not find key!"
    return false, last_compared
```
```C++
subtree_find2(node, k, p):
    if not node:
        return false, p
    if k == node.item:
        return true, node
    if k < node.item:
        subtree_find2(node.left, k, node)
    else:
        subtree_find2(node.right, k, node)
```
(5)
```C++
find_prev(k):
    if k <= first_in_tree(tree).item:
        output "no previous node for k!"
        return
    success, node = subtree_find(tree, k)
    if success:
        return predecessor(node)
    if k < node:
        return predecessor(node)
    return node
```
(6)
```C++
insert(x):
    k = x.key
    success, node = subtree_find(tree, k)
    if success:
        node.item = x
    else if k < node.item:
        put x at node.left
    else:
        put x at node.right
```
### Binary Search and find_prev/find_next Rationale
* We do binary search on binary tree or sorted array. Failed binary search gives info between which two nodes(array elements) our queried key is in.
* For failed search on tree, suppose last compared node (the node where we fell of the tree) is "node". If key k < node.item and predecessor(node) exists, k must also be bigger than predecessor(node).item; if k > node.item and successor(node) exists, k must also be smaller than successor(node).item.
    **Prove**: suppose k > node.item
    1. node.right not exist.
    2. successor(node) must be its ancestor.
    3. k < successor(node).
* In fact, a binary search on sorted array can be mapped to a unique BST since we know exactly which nodes to compare first and second and so on, as compared with the exponential number of binary trees that encode the same sequence order. Then failed bianry search on array parallels that on tree. Suppose last compared element is at index "index". If k < array[index] and index > 0, k must be bigger than array[index-1]; if k > array[index] and index < len(array) - 1, k must be smaller than array[index+1].

|Binary Tree Sequence Operations:|Implementations:|Complexity:
|---|---|---
|get_at(i)|iteratively compare i with size of left subtree $^{(7)}$|O(h)
|set_at(i,x)|set get_at(i) with x|O(h)
|insert_at(i,x)|insert x after node get_at(i), update ancestors of x' size fields up the tree $^{(8)}$|O(h)
|insert_first(x)|same as insert_at(i,x)|O(h)
|insert_last(x)|same as insert_at(i,x)|O(h)
|delete_at(i)|delete node get_at(i) and get the parent p of deleted leaf node, update size fields from p up the tree $^{(9)}$|O(h)
|delete_first()|same as delete_at(i)|O(h)
|delete_last()|same as delete_at(i)|O(h)

### Data Structure Augmentation
*subtree properties* : can be calculated from nodes in subtree in constant time. Each node can have O(1) extra properties, and every binary tree operation will still take O(h) time. 
* Tree edit operations (insert/delete) in the end insert or delete a leaf.

* *subtree properties* : size, sum, max, height. 

* *non-subtree properties*: depth, global properties like index.


(7)
```C++
get_at(i):
    return subtree_at(tree, i)
subtree_at(node, i):
    if i == node.left.size:
        return node
    else if i < node.left.size:
        return subtree_at(node.left, i)
    return subtree_at(node.right, i - node.left.size - 1)

set_at(i, x):
    get_at(i).item = x
```
(8)
```c++
insert_at(i, x):
    node = get_at(i)
    insert_before(node, x)
    x.size = 1
    p = x.parent
    while p:
        p.size = p.left.size + p.right.size +1
        p = p.parent
```
(9)
```C++
delete_at(i):
    node = get_at(i)
    p = subtree_delete(node)
    while p:
        p.size = p.left.size + p.right.size + 1
        p = p.parent
```
## Balanced Binary Tree and Rotation
* *Balanced Binary Tree* : $h=\text{O}(\log n)$
* *AVL Tree* : for every node, abs(node.left.height - node.right.height) <= 1
* AVL trees are balanced.

**Prove**: 
Given AVL tree of height h and number of nodes n. To prove h is at most $\Theta (\log n)$ is to prove n is at least $\Theta (2^h)$. 
So we make an AVL tree of height h and fill in with minimum nodes. 
Let $x_h$ be the least number of nodes in AVL tree of height h. Then,
$$
\begin{aligned}
x_1 &= 1\\
x_2 &= 2\\
x_h &= 1 + x_{h-1} + x_{h-2} \\
    &>2x_{h-2} \\
    &= 2^{\lfloor {h/2} \rfloor} \\
    &= \Theta (2^h).
\end{aligned}
$$
### Binary Tree Edit Operations Balanced
* Rotation exploits that there are many binary tree representations of one traversal oder. Rotation operations preserve traversal order.

(10)
```c++
insert_after_balanced(x, z):
    insert_after(x, z)
    z = z.parent
    while z:
        skew = getSkew(z)
        if skew > 1 or skew < 1:
            balance(z, skew)
            break;
        else:
            calHeight(z)
            update all other properties of z
        z = z.parent

subtree_delete_balanced(z):
    x = subtree_delete(z)
    while x:
        skew = getSkew(x)
        if skew > 1 or skew < 1:
            x = balance(x, skew)
        else:
            calHeight(x)
            update all other properties of x
        x = x.parent

getSkew(node):
        return node.left.height - node.right.height

balance(x, skew):
    z = null
    if -2 == skew:
        y = x.right
        if 1 = getSkew(y):
            z = y.left
            right_rotate(y)
        left_rotate(x)
    else if 2 == skew
        y = x.left
        if -1 = getSkew(y):
            z = y.right
            left_rotate(y)
        right_rotate(x)
    calHeight(x)
    calHeight(y)
    if z:
        calHeight(z)
        return z
    else:
        return y
        
right_rotate(b):
    a = b.left
    x = a.left
    y = a.right
    z = b.right
    a.parent = b.parent
    if b == b.parent.left:
        b.parent.left = a
    else:
        b.parent.right = a
    a.right = b
    b.parent = a
    b.left = y
    y.parent = b

left_rotate(a):
    b = a.right
    x = a.left
    y = b.left
    z = b.right
    b.parent = a.parent
    if a == a.parent.left:
        a.parent.left = b
    else:
        a.parent.right = b
    b.left = a
    a.parent = b
    a.right = y
    y.parent = a

calHeight(x):
    hl = x.left ? x.left.height : 0
    hr = x.right ? x.right.height : 0
    x.height = max(hl, hr) + 1
```
