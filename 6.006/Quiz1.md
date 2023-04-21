### Problem 2.
a.
(1).Worst-case:
$\Theta(n^2)$
(2).Expected:
$\Theta(n)$
b.
(1).Worst-case:
$\Theta(n+k)$
(2).Expected:
$\Theta(n+k)$

### Problem 3.
a.
A.
b.
B,C,D,E,F,G
c.
H,I,J,F,G
```
            A
           B C
         D E F G
        HI J
```

### Problem 4.
a.
before:
[93, 85, 38, 23, 63, 11, 13, 17]
after:
[85, 63, 38, 23, 17, 11, 13]
b.
(17, 85, 11, 13)

### Problem 5.
a.
counting sort
(u = n)
b.
merge sort
c.
selection sort in $\text{O}(n)$ time.
d.
radix sort
(u = $16n^3$)
(u < $256n^{3\log{2}}$)
### Problem 6.
1. sort $A$ and $B$ in increasing order.
2. For each $c\in C$, repeat step 3 until some $a\in A$ and $b \in B$ adds up to $-c$.
3. Start with $i$ pointing to the minimum element in $A$, $j$ pointing to largest element in $B$. If $A[i]+B[j]=-c$, a triple sum is found and algorithm exits. Else if $A[i]+B[j]<-c$, forward $i$ by one. Else decrement $j$ by one. Repeat until $i$ or $j$ points to one past end.
Running time is worst-case $\text{O}(n^2).$

Correctness:
Loop Invariant: at the start of each loop with $i=i^*,j=j^*$, 
1. for any $1<=i<i^*, 1\le j\le n$, $A[i]+B[j] \neq -c$.
2. for any $j^*<j \le n, 1\le i\le n$, $A[i]+B[j] \neq -c$.

Prove:
* Init: Trivally true when $i^*=0,j^*=n-1$.
* Each round of loop:
  $A[i]+B[j]!=-c,i<i^*\  \text{or}\ j>j^*$.
  * $A[i^*]+B[j^*]>-c$. Because $A[i]>=A[i^*],i>=i^*$, we have $A[i]+B[j^*]\neq -c,-1\le i\le n$. Decrease $j$ by 1 and invariant is restored.
  * $A[i^*]+B[j^*]<-c$. Because $B[j]<=B[j^*],j<=j^*$, we have $A[i^*]+B[j]\neq-c$ for any $j$. Increase $i$ by 1 and invariant is restored. 
* Exit: Algorithm either exits with $A[i]+B[j]=-c$ for some $i$ and $j$ and a triple sum is found. Otherwise algorithm exists with $i^*=n+1$ or $j^*=0$. No $A[i]$ and $B[j]$ add up to $-c$ for any $i$ in the first case or for any $j$ in second case. i.e. for any pair of $i,j\in A\times B$, $A[i]+B[j]$ is not equal to $-c$.
### Problem 7.
Starting from $v$ and go up the tree, with each of its ancestors $x$ encountered, we can compute the index $\text{index}(x,v)$ of $v$ in subtree rooted at $x$ in worst-case time $\text{O}(1)$. Because we already know index of $v$ in $x$'s child subtrees.
$$
\text{index}(x,v) = \begin{cases}
x.left.size 
&\text{if x == v}\\
x.left.size + 1 +\text{index}(x.right, v)
&\text{if x in x.right}\\
\text{index}(x.left, v) 
&\text{if x in x.left}
\end{cases}
$$
Index of node $v$ in the traversal order of $T$ is just $\text{index}(T.root,v)$. The path from $v$ to root takes at most time $\text{O}(\log{n})$.

### Problem 8.
(mistakes:
Take pipes' distinct positive integer labels as continuous integer starting from 1..
Did not consider using additional HashTable $H$ to keep track of nodes in heap, therefore allowing heap size continue to grow and could't reach operation time $\text{O}(\log{k})$.)
We need following data structures:
1. Hash table $A$ is a nested data structure that mapps pipe label $p_i$ to a set AVL tree $T_i$, which is a set of unpatched holes' distance from the front of pipe $p_i$.
  * Augment each of $T_i$'s nodes $x$ with their predecessors $pre(x)$ and successors $suc(x)$. To maintain these two properties while adding and deleting nodes is just like in linked lists.
  * Augment each of $T_i$'s nodes with property $min=(value,d)$. $value$ represents the minimum of the mutual distances between holes within node's subtree. $d$ refers to the left hole of corresponding consecutive hole pair, or a lonely hole. $min.value$ of any leaf node is a large enough value LARGE_DIST.
$$
  x.min.value=\begin{cases}
  \text{LARGE\_DIST}&\text{if x is leaf}\\
  min(x.left.min.value,x.right.min.value,x.key-pre(x).key,suc(x).key-x.key)&\text{otherwise}
  \end{cases}
$$
2. Heap $P$ mapps the minimum mutual distance of any pipe that contains unpatched holes to corresponding to-be-patched-next hole in that pipe, represented by the tuple of pipe and distance to the front of pipe $(p,d)$.  
3. Hash Table $H$ that mapps each hole in heap $P$ to its location in $P$.

To implement $\text{initialize}(H)$, for each pipe $p_i$ make an AVL tree containing only root node $(p_i,d_i)$ and insert the tree into $A$. Make min-heap $P$ with $n$ nodes, each node keyed by priority LARGE_DIST and valued by hole $(p_i,d_i)$. $H$ records reference to these nodes in $P$. Time is expected $\text{O}(n)$.

To implement $\text{report}(p_i,d_i)$, first get $p_i$'s tree $T_i$. Secondly, create new node $x$ keyed on $d_i$, insert into $T_i$ and update properties $pre$, $suc$ and $min$ upwards to the root. If $T_i.root.min$ changes:
  * delete old node in $P$ and $H$ by getting node's pointer in $H$.
  * make new node $x = T_i.root.min$ and insert to $P$, store the pointer in $H$.
Because anytime $P$ and $H$ contains at most $k$ nodes. Time is amortized expected $\text{O}(\log{k})$.

To implement $\text{patch}()$, delete_min() from heap $P$, and obtain the deleted node $z$, delete $z$ in $H$, access into $A[z.hole.p]$, delete node keyed on $z.hole.d$. Time is amortized expected $\text{O}(\log{k})$.



### Problem 9.
Maintain a set AVL tree $T$, where each node represents an active user range (l,r). That is, $T$ mapps each of the left end point $l$ of active range to the corresponding right end point $r$. augment each node with property $range$ which is the biggest active range within node $x$'s subtree.
$$
x.range=\text{biggest\_range}((x.l,x.r),x.left.range,x.right.range)
$$
Since $x.range$ can be computed using just the info of two children, such property can be maintained without affecting AVL asymptotic performance.
Also keep a set AVL tree $T_2$ mapping IDs to statuses.
* To implement $\text{build}(D)$, create new node $x$, $x.l = min\{d_0..d_{n-1}\},x.r=max\{d_0..d_{n-1}\}, x.range=(x.l,x.r)$. Make $x$ the root node of $T$. Also build AVL tree $T_2$ by inserting $n$ active users in.
* To implement $\text{toggle\_status}(d_i)$, first we want to examine the status of $d_i$ in $\text{O}(\log{n})$. Also find predecessor and successor of $d(i)$ in $T_2$ if exists: $pre(d_i)$ and $suc(d_i)$.
  * If active, search for range in $T$ containing $d_i$ in $\text{O}(\log{n})$ time. Break $x$ into two nodes if could, i.e. delete $x$ from $T$ and insert two new nodes $y,z$, where $y.l=x.l,y.r=pre(d_i), z.l=suc(d_i),z.r=x.r$.
  * If inactive, search for node $y$ in $T$ with right end point $pre(d_i)$ and $z$ whose left endpoint equals $suc(d_i)$. If both $y$ and $z$ exist, delete $z$ and let $y.r=z.r$. Otherwise rewrite $y.r=d_i$ or $z.l=d_i$ in the cases $y$ or $z$ exists respectively. Lastly if none of $y$ or $z$ can be found, make and insert a new node $x$ where $x.l=x.r=d_i$.
  * toggle the status in $T_2$.
* To implement $\text{big\_active\_range()}$, simply return $T.root.range$ in $\text{O}(1)$ time.

Note: each range in $T$ is non-overlapping.
Note: A different approach would be keeping all users in one tree, active or inactive. Augment each node by two consecutive active ranges at left and right ends, with which largest active range in subtree con be computed in $\text{0}(1)$. But the key rational is the same -- when a user status toggled, merge of split the largest active range of ancestors to the root.
