### 24-4 Gabow’s scaling algorithm for single-source shortest paths

-----
**Input:**
    directed graph $G=(V,E)$
    $w(u,v)\ge 0,\forall(u,v)\in E$
    $W=\max_{(u,v)\in E}\{w(u,v)\}$
    all vertices reachable from  source $s$
    $|E|\ge |V|-1$

-----
**Output:**
    computing SSSP in $\text{O}(E\log W)$ time

-----
Some values to have around:
$k=\lceil\log(W+1) \rceil$
$w_i(u,v)=\lfloor w(u,v)/2^{k-i}\rfloor ,i=1,2,...,k$
Define $\delta_i(u,v)$ as the shortest-path weight from vertex $u$ to vertex $v$ using weight function $w_i$. $\delta_k(u,v)=\delta(u,v)$

-----
**a.**

Suppose that for all vertices $v\in V$,we have $\delta(s,v)\le |E|$. Show that we can compute $\delta(s,v)$ for all $v\in V$ in $\text{O}(E)$ time.

**Solution:**
Using Dijkstra, $T=B+|V|\cdot C+|E|\cdot D$ where
B = time to perform Build_Queue(G. V)
C = average time to perform Delete_Min()
D = average time to perform Decrease_Key(handle, key)

Here we can implement the changable priority queue as a direct access array of length $|E|$ since $\delta(s,v)\le |E|,\forall v\in V$. (refer to 24.3-8)
$\Rightarrow$
$B=\text{O}(|E|)$
$C=\text{O}(\frac{|E|}{|V|})$
$D=\text{O}(1)$
$T=\text{O}(|E|)$

-----
**b.**

Show that we can compute $\delta_1(s,v)$ for all $v\in V$ in $\text{O}(E)$ time.

**Solution:**
$w_1(u,v)\le 1, \forall(u,v)\in E \Rightarrow \delta_1(s,v)\le |V|-1\le |E|,\forall(u,v)\in E $.

-----
**c.**

**Solution:**

If the $i$-th significant bit of $w(u,v)$ is 0, $w_i(u,v) = 2w_{i-1}(u,v)+1$; otherwise $w_i(u,v) = 2w_{i-1}(u,v)$.

$$
\delta_i(s,v)=\sum_{\forall(u,v)\in SP(s,v)}w_i(u,v)
\\\le \sum_{\forall(u,v)\in SP(s,v)}2w_{i-1}(u,v)+1
\\\le 2\delta_{i-1}(s,v)+|V|-1.
\\ 
\\\delta_i(s,v)\ge \sum_{\forall(u,v)\in SP(s,v)}2w_{i-1}(u,v)
\\=2\delta_{i-1}(s,v)
$$

-----
**d.**

**Solution:**

$$
\hat w_i(u,v)=w_i(u,v)+2\delta_{i-1}(s,u)-2\delta_{i-1}(s,v)
$$

Prove that for $i=2,3,...,k$ and all $u,v\in V$,the “reweighted” value $\hat w_i(u,v)$ is a nonnegative integer.

$$
\hat w_i(u,v)=w_i(u,v)+2\delta_{i-1}(s,u)-2\delta_{i-1}(s,v)
\\\ge 2w_{i-1}(u,v)+2\delta_{i-1}(s,u)-2\delta_{i-1}(s,v)
\\\ge 2\big(w_{i-1}(u,v)+\delta_{i-1}(s,u)-\delta_{i-1}(s,v)\big)
\\\ge 0
$$

-----
**e.**

**Solution:**

If we assign value $h(v),\forall v\in V$ to each vertex, and reweight all edge weights:

$$
w'(u,v) = w(u,v) + h(u) - h(v)
$$

all pairs single path will be reserved:

$$
\delta'(s,t)=\sum_{\forall(u,v)\in SP(s,t)} w'(u,v)\\=\sum_{\forall(u,v)\in SP(s,t)} \big (w(u,v) + h(u) - h(v)\big )
\\=\sum_{\forall(u,v)\in SP(s,t)} w(u,v) +h(s)-h(t)
\\=\delta(s,t) +h(s)-h(t)
$$

because all paths from $s$ to $t$ will change by the same value.

Now by taking $h(v)=2\delta_{i-1}(s,v),\forall v\in V$ and reweighting $\hat w_i(u,v)=w_i(u,v)+2\delta_{i-1}(s,u)-2\delta_{i-1}(s,v)$ we have 

$$
\hat\delta_i(s,t)=\delta_i(s,t) +2\delta_{i-1}(s,s)-2\delta_{i-1}(s,t)
\\=\delta_i(s,t)-2\delta_{i-1}(s,t)
\\\le |V|-1
\\\le |E|
$$

-----
**f.**
Show how to compute $\delta_{i}(s,v)$ from $\delta_{i-1}(s,v)$ for all $v\in V$ in $\text{O}(E)$ time, and conclude that we can compute $\delta(s,v)$ for all $v\in V$ in $\text{O}(E\log W)$ time.

**Solution:**
Because $\hat\delta_i(s,v)\le |E|$ we can always compute $\hat\delta_i(s,v),\forall v\in V$ in $\text{O}(E)$ time. Because the way we reweights graph preserves shortest path, we can readily compute $\delta_{i}(s,v),\forall v\in V$ as $\delta_{i}(s,v)=\hat\delta_i(s,t)+2\delta_{i-1}(s,v)$ in $\text{O}(V)$ time. Therefore we can compute $\delta_1(s,v),\delta_2(s,v),...,\delta_k(s,v)$ in sequence in $\text{O}(E\log W)$ time.


