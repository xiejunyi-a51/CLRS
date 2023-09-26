### Orthogonal Range Search Problem ⭐

**Input:** A set of $n$ points $S$ in 2-D(3-D) dimention. A query consists of a box: $x_{min},x_{max},y_{min},y_{max}(,z_{min},z_{max})$.
**Output:** After preprocessing, we are able to process a query of computing number of points $k$ contained in a box in $\log^2{n}(\log^3{n})+\text{O}(k)$ time.
**Algorithm:** Range tree.
**Application** could be indexing in database systems.

**1-D algorithm**
1. Given range $(x,y)$. Start from root and try to find both $x$ and $y$. When the path starts to diverge, we have found the lowest common ancestor $z$.
2. Let $L$ be the sum of the value $1+p.right.size$ of every node $p$ on path from $z$ to $x$, excluding $z$, that has key bigger than $x$. 
Samewise $R$ is the sum of $1+p.left.size$ for every node on path from $z$ to $y$ excluding $z$ that has smaller key than $z$.
**Proof:**
This algo sounds familiar with $Rank(x)$. In fact $L$ is the *right rank* of $x$ in subtree $z.left$ and $R$ is the *left rank* of $y$ in subtree $z.right$.
3. Return $L+R+1$.

**Modification**
If $x,y$ are not in tree. Substitute them with the successor of $x$ and predecessor of $y$.

**2-D algorithm**
For each node $p$ in $x$-tree, augment it to point to another $y$-tree consisting of exactly the same nodes in subtree rooted at $p$ in original $x$-tree. Totoal space would be $n\log{n}$ since each node is contained in (1+#ancestor) $y$-trees. 