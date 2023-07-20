### Karp’s minimum mean-weight cycle algorithm
**Solution:**
a.
 If $G$ contains negtive-weight cycles, the $\mu^* <0$.

General $\delta(s,v)=\min_{0\le k} \delta(s,v)$. Since there is no negtive weight cycles in $G$, $\delta(s,v),\forall v\in V$ is finite and there exist simple shortest path from $s$ to $v$, which have atmost $n-1$ edges. Therefore if $\mu^*=0,\delta(s,v)=\min_{0\le k\le n-1} \delta(s,v),\forall v\in V$.

b.

$$
\max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}=\frac{\delta_n(s,v)-\delta(s,v)}{n-k}\ge 0
$$

c.
Triangle equality states $\delta(s,v)\le \delta(s,u)+x$. But if $\delta(s,v)<\delta(s,u)+x$, then there exists a shorter path from $s$ to $u$ with $\delta'(s,u)\le \delta(s,v)-x<\delta(s,u)$. Contradicts.

d.
Pick any vertex $v$ on $c$ with $\delta(s,v)=\delta_{k*}(s,v)$, $k^*$ is the number of edges on simple shortest path. Start from $v$ and walk along $c$ until the next $n-k^*$ vertex $u$. The number of edges in $c$ is $m$. We have $\delta(s,u)=\delta(s,v)+ (n-k^*)\mod m$. And by definition $\delta_n(s,u)=\delta(s,u)$. Therefore exists $u$ on $c$ such that

$$
\max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}=\frac{\delta_n(s,v)-\delta(s,v)}{n-k}=0.
$$

e.
We already showed that if $\mu^*=0$,there must exist minimum weight cycle $c$ and vertex $v$ on $c$ such that

$$
\max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}=\frac{\delta_n(s,v)-\delta(s,v)}{n-k}=0.
$$

Now we show $0$ is lower bound on equation for all $v\in V$.

For any $v\in V$, either
Case 1: $\delta_n(s,v)=\infty$, clearly equation equals $\infty>0$.
Case2: $\delta_n(s,v)$ is finite but the $n$-edges shortest path does not include shortest path that corresponds to $\delta(s,v)$. Then $\delta_n(s,v)-\delta(s,v)>0\Rightarrow \max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}>0$.
Case3: $\delta_n(s,v)$ is finite and the $n$-edges shortest path constitutes of shortest path$. Then $\max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}=0$.

$$
\max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}\ge 0,\forall v\in V
$$

Proof completed.

f.
Mean cycle weight increase by $t$ for all cycles. Therefore $\mu^*$ increases by $t$.

As in (e) we show that 

$$
\max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}\ge t,\forall v\in V
$$

First notice $k$-edges shortest paths are perserved. Then

$$
\max_{0\le k\le n-1} \frac{\delta'_n(s,v)-\delta'_k(s,v)}{n-k}=\max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)+(n-k)\cdot t}{n-k}
\\=t+\max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}\ge t.
$$

Because there exist $\mu^*=t$, 

$$
\min_{v\in V} \max_{0\le k\le n-1} \frac{\delta_n(s,v)-\delta_k(s,v)}{n-k}=t,\forall v\in V
$$

g.

Algorithm:
Step 1. In $n$ steps BFS we can compute $\delta_0(s,v),\delta_1(s,v),...,\delta_{n-1}(s,v)$ and also $\delta(s,v)=\min_{0\le k\le n-1} \delta(s,v)$. It takes $\text{O}(n\min(V,E))=\text{O}(VE)$.
Step 2. Find minimum $\mu^*$ for all $v\in V$ and return $\mu^*-t$.