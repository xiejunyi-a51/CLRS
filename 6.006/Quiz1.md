### Problem 2.
a.
(1).Worst-case:
$\Theta(n^2)$
(2).Expected:
$\Theta(n)$
b.
(1).Worst-case:
$\Theta(k)$
(2).Expected:
$\Theta(k)$

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
selection sort
d.
radix sort
(u = $16n^3$)

### Problem 6.
1. sort $A$ and $B$ in increasing order.
2. For each $c\in C$, repeat step 3 until some $a\in A$ and $b \in B$ adds up to $-c$.
3. Start with $i$ pointing to the minimum element in $A$, $j$ pointing to largest element in $B$. If $A[i]+B[j]=-c$, a triple sum is found and algorithm exits. Else if $A[i]+B[j]<-c$, forward $i$ by one. Else decrement $j$ by one. Repeat until $i$ or $j$ points to one past end.
Running time is worst-case $\text{O}(n^2).$
### Problem 7.
Starting from $v$ and go up the tree, with each of its ancestors $x$ encountered, we can compute the index $\text{index}(x,v)$ of $v$ in subtree rooted at $x$ in worst-case time $\text{O}(1)$. Because we already know index of $v$ in $x$'s child subtrees.
$$
\text{index}(x,v) = \begin{cases}
x.left.size 
&\text{if x == v}\\
x.left.size + \text{index}(x.right, v)
&\text{if x in x.right}\\
\text{index}(x.left, v) 
&\text{if x in x.left}
\end{cases}
$$
Index of node $v$ in the traversal order of $T$ is just $\text{index}(T.root,v)$. The path from $v$ to root takes at most time $\text{O}(\log{n})$.

### Problem 8.
We need two data structures: one direct access array $A$, one Heap $P$.
1. Hash table is a nested data structure that mapps each of the integers $1..n$ to a set AVL tree $T_i$, which is the set of distances $d$ s of holes in pipe $p_i$. 
  * Augment $T_i$'s nodes $x$ s with their predecessors $pre(x)$ s and successors $suc(x)$ s. To maintain these two properties while adding and deleting nodes is just like in linked lists.
  * Augment $T_i$'s nodes $x$ s with property $min$, representing minimum of the mutual distances within node's subtree, attached with correponding node's key $dist$. The $min$ of leaf node is a large enough value LARGE_DIST.
$$
  x.min.value=\begin{cases}
  \text{LARGE\_DIST}&\text{if x is leaf}\\
  min(x.left.min.value,x.right.min.value,x.d-pre(x).d,suc(x).d-x.d)&\text{otherwise}
  \end{cases}
$$
2. Heap $P$ contains the minimum mutual distances in $n$ pipes: node $z=(z.priority,z.hole)=(z.priority,(z.hole.p,z.hole.d))=(T_i.root.min.value,(p_i,T_i.root.min.d))$.
To implement $\text{initialize}(H)$, make a direct access array $A$ of length $n+1$. Fill in each element $A[i],i>=1$ with an AVL tree containing only root node $(p_i,d_i)$. Make min-heap $P$ with $n$ nodes, each node with large enough priority LARGE_DIST and associated hole value $(p_i,d_i)$. Time is worst-case $\text{O}(n)$.
To implement $\text{report}(p_i,d_i)$, first get A'$i$th element $T_i$. Secondly, create new node $x$, $x.d=d_i$, insert into $T_i$ and update properties $pre$, $suc$ and $min$. If $T_i.root.min$ changes, insert into $P$ with $T_i.root.min$. Time is worst-case $\text{O}(\log{k})$.
To implement $\text{patch}()$, delete_min() from heap $P$ and obtain the deleted node $z$, access into $A[z.hole.p]$, delete node keyed on $z.hole.d$. Time is worst-case $\text{O}(\log{k})$.



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
  * If inactive, search for node $y$ in $T$ with right end point $pre(d_i)$ and $z$ whose left endpoint equals $suc(d_i)$. If both $y$ and $z$ exist, delete $z$ and let $y.r=z.r$. Otherwise rewrite $t.r=d_i$ or $z.l=d_i$ in the cases $y$ or $z$ exists respectively.
  * toggle the status in $T_2$.
* To implement $\text{big\_active\_range()}$, simply return $T.root.range$ in $\text{O}(1)$ time.

