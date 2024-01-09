### Problem 9-1. Coin Crafting ⭐
Input: 
$n$ coins.
$n$ golden objects $i=0\to n-1$.
$V[i]$ is the positive integer purchase price of object $i$.
$L[i]$ is the positive integer melting number of object $i$.
Subprobelm $R(i, j)$: maximum revenue using just objects $i,...,n-1$ and within $j$ coins. $0\le i \le n, 0\le j \le n$.

Relation:

$$
R(i,j)=\max\{R(i+1,j),V[i] + R(i+1,j-L[i])\text{ if } j\ge L[i]\}
$$

Topo: decreasing $i$.
Base: $R(n,j)=0=R(i,0)$.
Original Problem: $R(0,n)$.
Time: $T=\Theta(n^2)$

### Problem 9-2. Career Fair Optimization ⭐
Subproblem $C(w,t)$: Maximum coolness when there are $t$ minutes left and $w$ extra weight left in bag, and Tim is already standing at the back of any booth line.

Relate:

$$
C(w,t) = \max\{
C(b,t-(1+h)) \text{ if }t\ge h    
\}
\cup
\{
c_i+C(w-w_i,t-(1+t_i))|w\ge w_i,t\ge t_i,0\le i \le n-1
\}
\cup
\{0\}
$$

**Diff with official solution in that I think tim can get the coolness as long as remaining time $t$ is enough for waiting in line time $t_i$, not requiring the extra 1 minute to get back in line.**

Topo: increasing $t$.
Base: $C(w,0)=C(w,-1)=0$.
Original: $C(b,k)$.
Time: $\Theta(bkn)$.

### Problem 9-3. Protein Parsing

Subproblem $x(i)$: the maximum value of any division of the DNA strand suffix $S[i :]$.

Relate:

$$
x(i)=\max\{x(i+1),1+x(i+
\min\{1\le j\le k,i+j\le n,m(i,i+j)\in P\})
\}
$$