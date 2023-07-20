### 24-2 Nesting boxes
a. If box $X=(x_1,x_2,...,x_d)$ is nested in box $Y=(y_1,y_2,...,y_d)$ and $Y$ is nested in $Z=(z_1,z_2,...,z_d)$ then $X$ is nested in $Z$.
**Proof:**
There exists some permutation of $X$ such that $x_{ik}<y_k,1\le k\le d$. And there is permutation of $Z$ such that $y_k<z_{jk},1\le k\le d$

$$
\Rightarrow \forall k,x_{ik}< y_k < z_{jk}.
$$

Therefore nesting relationship is transitive.

b. $X=(x_1,x_2,...,x_d)$ nests in box $Y=(y_1,y_2,...,y_d)$ if and only if $\forall i$, the $i$-th order $x$ is smaller than the $i$-th order $y$: $x_{r_i}<y_{r_i}$.

$\Leftarrow$ True by nesting definition.
$\Rightarrow$ If $X$ is nested in $Y$, first sort $Y$ in increasing order:$y_1<y_2<...<y_d$, i.e. $y_k=y_{r_k}$. Then exists a permutation of $X$ such that $x_{ik}<y_k,1\le k\le d$. Observe the number of $x$ s smaller than $y_k$ is at least $k$:

$$
\sum_{x_j<y_{r_k},\forall j}1\ge k, \forall k.
$$

Assume $\exist i, x_{r_i}\ge y_{r_i}$, then the number of $x$ s smaller than $y_{r_i}$ is atmost $i-1$:

$$
\sum_{x_j<y_{r_i},\forall j}1 \le i-1,
$$

which contradicts with former observation. By proof of contradiction the statement is true.

**Algorithm:**
Sort both boxes $X$ and $Y$ in $\text{O}(d\log d)$ time, then compare value one by one in $\text{O}(d)$ time. If $x_{r_i}<y_{r_i},\forall i$, $X$ nests within $Y$, and vice versa.

c.

-----
**Idea1:** Longest monotonically increasing subsequence(LMIS) Algo does not apply here since to achieve $\text{O}(n\log n)$ among all LMIS of length-$i,\forall i$, we need to know the smallest ending element. But that is impossible here for some boxes doesn't compare.

-----
**Idea2:** Contruct a DAG $G=(V,E)$. $V$ is the set of all boxes. Add an edge $(u,v)$ if box $v$ nests within box $u$. Topological sort $G$. Following topologically sorted order, relax all outgoing edges of $v$:

```C++
relax(u,v)
    if u.a+1>v.a:
        v.a=u.a+1
        //v.a is the length of longest path ending at v
```

$$
v.a=\max (0,\max_{u\in Adj^{-}(v)}u.a + 1 )
$$

-----
**Algorithm:**
1. Sort the dimentions of each box in $\text{O}(nd\log d)$.
2. Construct graph $G$. Compare all pairs of boxes in $\text{O}(n^2d)$, add an edge $(u,v)$ if box $v$ nests within box $u$.
3. Topoligical sort $G$ in $\text{O}(|V|+|E|)=\text{O}(n^2)$.
4. Following topologically sorted order, relax all outgoing edges of $v$ in $\text{O}(|V|+|E|)=\text{O}(n^2)$.
5. Return $\max v.a,\forall v\in V$.

**Analysis:**
Total running time is $\text{O}(nd(\log d + n))$.