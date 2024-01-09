## Dynamic Programming
### longest common subsequence problem ⭐
Subproblem for multiple sequence inputs $\Rightarrow$ product of multiple subproblem spaces

    Given sequences A,B, find longest sequence L that's subsequence of both A and B. 

Define subproblem $L(i,j)$: Find LCS between suffixes $A[i:]$ and $B[j:]$.

$$

\begin{cases}
L(i,j) = 1+L(i+1,j+1) \quad\text{if A[i]==B[j]}\\
L(i,j) = \max(L(i+1,j),L(i,j+1)) \quad\text{otherwise}\\
L(|A|,j) = 0 = L(i,|B|)
\end{cases}
$$

If $A[i]!=B[j]$, $A[i]$ and $B[j]$ can not both be in LCS between $A[i:]$ and $B[j:]$. Then there are two possible cases to consider: $A[i]$ not in LCS or $B[j]$ not in LCS.

$T=\Theta(|A||B|)$.

_Further memory reduction can be applied._

### longest increasing subsequence problem ⭐

    Given sequences A, find longest [strictly] increasing subsequence.

_If elements are restricted to 26 English letters, problem can be solved in linear time._

Define subproblem $L(i)$: find LIS of suffix $A[i:]$ that starts with $A[i]$.

_**Subproblem expansion** let us add more constraints to subproblems, similar idea as Layered Graph_

$$
\begin{cases}
L(i) = 1 + \max\{L(j)|i<j\le n,A[i]<A[j]\}\cup \{0\}\\
L(|A|) = 0
\end{cases}
$$

Base: $L(n) = 0$
Original problem: $LIS(A)=\max L(i)$.
Time: $T=\Theta(|A|^2)$.

**What other question can we ask about subproblem features?**
Assume at some point $a_1,a_2,...,a_m$ has the smallest ending element among all length-$m$ increasing subsequence and $b_1,b_2,...,b_n$ has the smallest ending element among all length-$n$ increasing subsequence. $m > n \Leftrightarrow a_m > b_n$.

**Proof:**
$\Rightarrow$ If $m>n$ and $a_m\le b_n$, then subsequence $a_1,a_2,...,a_n$ will be a length-$n$ increasing subsequence with smaller ending element $a_n$. Contradicts with assumption. By proof of contradiction, if $m>n$ then $a_m> b_n$.

$\Leftarrow$ Similarly if $a_m>b_n$ and $m<n$, then subsequence $b_1,b_2,...,b_m$ will be a length-$m$ increasing subsequence with smaller ending element $b_m$, By proof of contradiction, if  $a_m> b_n$ then $m>n$.

**LIS Recursive Algorithm with a little Augmentation:**
At the time calculating $LIS(i)$, we already know $LIS(i+1),...,LIS(|A|)$. Keep record of largest starting elements for LIS of each length, which is in sorted order. Binary search for longest LIS that has starting element bigger than $A[i]$. Add one to that size.

Time: $T=\Theta(|A|\log |A|)$.

## Subproblem Constraint & Expansion

### Bellman-Ford SSSP ⭐
Subproblem $d(s,v,k)$: single source shortest path from $s$ to $v$ using at most $k$ vertices.

Relate:

$$
d(s,v,k) = \min\{d(s,v,k-1)\}\cup\{d(s,u,k-1)+w(u,v)|u\in Adj^{-}(v)\}
$$

_Note that just by adding constraints $k$ we expand $k$ copies of the original graph and make it acyclic._

Topo: increasing $k$.
_Note that Topo. of SSSP in DAG problem is topological order of graph itself_

Base: $d(s,s,0)=0,d(s,v,0)=\infty$
Original problem: $d(s,v,|V|-1)$ if graph does not contain negtive weight cycle, which can be detected by $d(s,v,|V|)$.
Time: $T=\Theta(|V||E|)$.

### Floyd-Warshall APSP ⭐
First run Bellman-ford to detect negtive weight cycle. If exists, abort.

Give each vertex $v$ a label $i,1 \le i\le |V|$.
Subproblem $d(u,v,k)$: Shortest path to go from $u$ to $v$ using only vertices in $\{u,v\}\cup\{1,...,k\},0\le k\le |V|$.

Relate:

$$
d(u,v,k) = \min(d(u,v,k-1),d(u,k,k-1)+d(k,v,k-1))
$$

Topo: increasing $k$.
Base: 
if $u=v$, $d(u,v,0)=0$;
if $u\ne v,(u,v)\in E$, $d(u,v,0)=w(u,v)$
otherwise $d(u,v,0)=\infty$.

Original problem: $d(u,v,|V|)$ if graph does not contain negtive weight cycle.
Time: $T=\Theta(|V|^3)$. 

_Floyd-Warshall is suitable for dense graph while Johnson is for sparse graph._

### Arithmetic Parenthesization
Input: a string of $a_0$ $op_0$ $a_1$ $op_1$ $a_2$ $...$ $op_{n-2}$ $a_{n-1}$, where each $op_i\in\{+,\times\}$.
Output: Parenthesization that maximize value.

Subproblem $V(i,j)$: Maximize value of substring $a_i$ $op_i$ $...$ $op_{j-1}$ $a_{j}$.

Relate:

$$
V(i,j) = \max \{apply(op_k,V(i,k),V(k+1,j))|k=i\to j-1\} \quad\text{i<j},
$$

where 
$$
apply(op,x,y)=
\begin{cases}
x\times y \quad\text{if op=}\times\\
x+ y \quad\text{if op=}+
\end{cases}
$$

Topo: In increasing $j-i$ order.
Base: $V(i,i)=a_i$.
Original problem: $V(0,n-1)$.
Time: $T=\Theta(n^3)$.

_What if $a_i$ could be negtive?_
Then we need to solve both max and min value of each subproblem, which is also a form of subprobelm expansion.
Subproblem $V(i,j,opt)$: Maximize value of substring $a_i$ $op_i$ $...$ $op_{j-1}$ $a_{j}$ if $opt={max}$. Minimize value of substring $a_i$ $op_i$ $...$ $op_{j-1}$ $a_{j}$ if $opt={min}$.

Relate:

$$
V(i,j,max) = \max \{apply(op_k,V(i,k,op_1),V(k+1,j,op_2))|k=i\to j-1\,op1,op2\in\{min,max\}\} \quad\text{i<j}\\
V(i,j,min) = \min \{apply(op_k,V(i,k,op_1),V(k+1,j,op_2))|k=i\to j-1, op1,op2\in\{min,max\} \} \quad\text{i<j}\\
$$

Topo: In increasing $j-i$ order.
Base: $V(i,i,opt)=a_i$.
Original problem: $V(0,n-1,max)$.
Time: $T=\Theta(n^3)$.

## Integer subproblems & Pseudopolynomial

### Subset Sum ⭐
    Given a set of integers A = {a0,a1,...,an-1}, Is there a subset of A that sum up to target T?
Subproblem $I(i,t)$: Is there a subset of $A[i:]$ that sum up to $t$? $0\le i\le n,0\le t\le T$

Relation:

$$
I(i,t)=
\begin{cases}
I(i+1,t)\text{ or }I(i+1,t-A[i])\text{ if t>=A[i]}\\
I(i+1,t)\text{ otherwise}
\end{cases}
$$

_Subproblem relation collapses many global choices. If the question were listing all subsets that sums up to target, time would be exponential._ ⭐
Imagine we already computed all $I(i,t)$. It would still take exponential time to reconstruct all subsets.

Topo: decreasing $i$.
Base:

$$
I(n,t)=\begin{cases}
0 \text{ if t>0}\\
1 \text{ if t=0}
\end{cases}
\\
I(i,0)=1
$$

Original Problem: $I(0,T)$.
Time: $\Theta(nT)$, which is in pseudopolynomial Time. ($T$ could be as large as exponential $n$)

Polynomial Time: Time increases in polynomial order of word sizes.
**Pseudopolynomial Time**: Time increases in polynomial order of word sizes and input integers.
Pseudo polynomial time becomes polynomial time when integers are within polynomial input word sizes.

## Main Features of Dynamic Programming
* Subproblems:
    * Prefix/suffixes: Bowling, LCS, LIS, Floyd–Warshall, Rod Cutting, Subset Sum
    * Substrings: Alternating Coin Game, Arithmetic Parenthesization
    * Multiple sequences: LCS
    * Integers: Fibonacci, Rod Cutting, Subset Sum
        * Pseudopolynomial: Fibonacci, Subset Sum
    * Vertices: DAG shortest paths, Bellman–Ford, Floyd–Warshall

* Subproblem constraints/expansion:
    * Nonexpansive constraint: LIS
    * $2\times$ expansion:AlternatingCoinGame(who goes first?),ArithmeticParenthesization (min/max)
    * $\Theta(1)\times$ expansion: Piano Fingering
    * $\Theta(n)\times$ expansion: Bellman–Ford
* Relation:
    * $\Theta(1)$ branching: Fibonacci, Bowling, LCS, Alternating Coin Game, Floyd–Warshall, Subset Sum
    * $\Theta(degree)$ all shortest path algos
    * $\Theta(n)$ branching: LIS, Arithmetic Parenthesization, Rod Cutting
    * Can you pick each object more than once? It's probably an Integer Subproblem type; else a standard suffix subproblem.
