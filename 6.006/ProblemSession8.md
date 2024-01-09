### Problem 8-1. Sunny Studies ⭐
    Given next n days and corresponding temperatures T[i], 0<=i<n. (never play more than two days in a row)

**Sol. 1 w/ Subproblem Expansion**
Subproblem $H(i,j)$: maximize happiness on temperatures suffix $T[i:]$, with the state of having already played for $j={0,1,2}$ days.

Relation:

$$
H(i,j) = 
\begin{cases}
H(i+1,0) \quad \text{if j=2}\\
\max\{T[i]+H(i+1,j+1),H(i+1,0)\}\quad\text{if j=0,1}

\end{cases}
$$

ToPo. order: $i=n,n-1,...,0$
Base: $H(n,j)=H(n+1,j)=0$.
Original problem: $H(0,0)$.
Time: $T=\Theta(n)$.

**Sol. 2**
Subproblem $H(i)$: maximize happiness on temperatures suffix $T[i:]$, guaranteeing not played the day before.
Relation:

$$
H(i) = \max\{H(i+1), T[i]+H(i+2),T[i]+T[i+1]+H(i+3)\}
$$

ToPo. order: $i=n,n-1,...,0$
Base: $H(n)=H(n+1)=H(n+2)=0$.
Original problem: $H(0)$.
Time: $T=\Theta(n)$.

### Problem 8-2. Diffing Data ⭐
    Given two files of n lines A,B. Minimize number of insertions and deletions that transform A to B. Swapping adjacent lines is allowed at most once for each line.

Subproblem $D(i,j)$: minimize insertions and deletions that transform suffixes $A[i:]$ to $B[j:]$.

Relation:

$$
D(i) = 
\begin{cases}
D(i+1, j+1) \quad \text{if A[i]=B[i]}\\
D(i+2, j+2) \quad\text{else if A[i]=B[i+1], A[i+1]=B[i]}\\
\min\{1+ D(i+1,j),1+D(i,j+1)\} \quad\text{else}


\end{cases}
$$


* if $A[i]=B[i]$: continue with $i+1,j+1$
* else if $A[i]=B[i+1], A[i+1]=B[i]$: swap $A[i],A[i+1]$, continue with $i+2,j+2$
* else: can delete $A[i]$, continue with $i+1,j$;
or insert in A with line $B[j]$, continue with $i,j+1$.

ToPo. order: $i=n,n-1,...,0, j=n,n-1,...,0$
Base: $D(n+1, j)=n-j+1$, $D(i,n+1) = n-i+1$.
Original problem: $D(0,0)$.
Time: $T=\Theta(n^2)$.

### Problem 8-3. Building Blocks ⭐

**Sol. 1 w/ Subproblem Expansion**

Let $b_{i,j}$ represent block $b_i$ with $j$-th($j=0,1,2$) face on top. And let $d_{i,j}$ be its top face dimentions,$h_{i,j}$ be its height. $h_{i,0}=w_i,h_{i,1}=h_i,h_{i,2}=l_i$
Subproblem $H(i,j)$: Maximum height built using $b_{i,j}$ as top block. 

Relation:

$$
H(i,j) = \max_{\{b_{s,t}|d_{s,t}>d_{i,j}\}} h_{i,j}+H(s,t)
$$

It's acyclic since $H(i,j)$ only depend on blocks with bigger dimensions.

ToPo. order: from bigger dimensions to smaller.
Base: $H(i, j)=h_{i,j}$ if $\{b_{s,t}|d_{s,t}>d_{i,j}\}=\emptyset$.
Original problem:
Add an artifical top block $b_{top}$ such that $d_{top,j}=0$ and $h_{top}=0$.
Original problem becomes $H(top,0)$.
Time: $T=\Theta(n^2)$.

**Sol. 2**
Because of the strict less than restriction, one orientation of a type of block can only appear once in solution. Since there are 3 of each type of block, just orient them in 3 diffrent ways and we never have to think of orientation choices again.

For each two blocks $b_i=w_i \times h_i \times l_i$ and $b_j=w_j \times h_j \times l_j$, compare top dimentions $d_i=w_i \times l_i$ with $d_j=w_j \times l_j$ and we have their relative ordering. With that we build a DAG representing blocks' topological order.

Subproblem $H(i)$: Maximum height built using $b_i$ as top block.

Relation:

$$
H(i) =  h_i + \max{\{H(j)|b_j\in Adj^{+}(b_i)\}}\cup \{0\}
$$

ToPo. order: from bigger dimensions to smaller.
Base: $H(i)=h_i$ if $\{b_j|d_j>d_i\}=\emptyset$.
Original problem:
Add an artifical top block $b_{top}$ such that $d_{top}=0$ and $h_{top}=0$.
Original problem becomes $H(top)$.
Time: $T=\Theta(n^2)$.

**Sol. 3**
Instead of pre-calculating the entire topological order graph in Sol. 2, we could sort blocks lexicographically. Then for any two blocks $b_i,b_j$, $b_i$ is to the left of $b_j$, we know $w_i\le w_j$, therefore $b_i$ is possible to be on top of $b_j$, but not otherwise. This way we solve the subproblems in a suffix approach rather than in a graph approach.

Subproblem $H(i)$: Maximum height built using $b_i$ and any of blocks from $B[i+1,:]$

Relation:

$$
H(i) =  h_i + \max{\{H(j)|j>i,d_j>d_i\}}\cup \{0\}
$$

### Problem 8-4. Princess Plum ⭐
    Given n x n grid forest where each grid square contains either a tree, mushroom, or is empty. Maximize mushrooms Pricess can pick on a quick path from top left square to bottom right square. Also return the number of paths to achieve that.

Quick path means Pricess can only go right or down.

Subproblem: $P(i,j)=M(i,j),N(i,j)$: maximum mushrooms Pricess can pick on a quick path from $(i,j)$ to $(n-1,n-1)$, and the number of different paths to do that.

Define function of a grid 

$$
\begin{aligned}
v(i,j) &= 1 \quad\text{if (i,j) contains mushroom}\\
v(i,j) &= 0 \quad\text{if (i,j) is empty}\\
v(i,j) &= -\infty \quad\text{if (i,j) contains tree}
\end{aligned}
$$

Relation:

$$
M(i,j)= v(i,j) + \max\{M(i+1,j),M(i,j+1)\}\\
N(i,j)= 
\begin{cases}
0\quad\text{if M(i+1,j)= }-\infty\text{ =M(i,j+1)}\\
N(i,j+1)\quad\text{else if M(i,j+1)>M(i+1,j)}\\
N(i+1,j)\quad\text{else if M(i+1,j)>M(i,j+1)}\\
2M(i+1,j)\quad\text{otherwise M(i+1,j)=M(i,j+1)}\ge0\\
\end{cases}
$$

ToPo. order: from bottom right corner to top left corner.
Base: 
$M(n-1,n-1) = v(n-1,n-1), N(n-1,n-1) = 1$.
$M(n,j) = -\infty = M(i,n)$.
$N(n,j) = 0 = N(i,n)$.
Original problem: $M(0,0),N(0,0)$.
Time: $T=\Theta(n^2)$.