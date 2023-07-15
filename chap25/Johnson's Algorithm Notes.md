## APSP Johnson's Algorithm
**Input:** Graph $G=(V,E)$. 

-----

**Output:** If detect there is negtive weight cycles in $G$, abort. Otherwise ouput all pairs shortest path.

-----
**Idea1:** If we can change graph weights in a way that shortest path $\delta(s,t),\forall s,t\in V$ is perserved and $w(u,v)\ge 0,\forall (u,v)$. Then APSP can be achieved by using Dijkstra $|V|$ times.

-----
**Idea2:** Assign vertex $v$ with integer $h(v)$, add $h(v)$ to every outgoing edges of $v$ and subtract $h(v)$ to every incoming edges of $v$. shortest path in graph is perserved.
**Proof:**
Assume path $p:s\leadsto t$.
Case 1. $s\neq v,t\neq v$.
a. If $s\leadsto t$ does not go through $v$,then its path weight doesn't change.
b. If $s\leadsto t$ passes through $v$, path weight doesn't change since new path weight is old weight plus $h(v)$ minus $h(v)$.
$SP(s,t)$ is preserved.
Case 2. $s=v$.
All path weight from $s$ increases by $h(v)$. $SP(s,t)$ is preserved.
Case 3. $t=v$.
All path weight ending at $t$ decreases by $h(v)$. $SP(s,t)$ is preserved.

-----
**Idea3:** To make $w(u,v)+h(u)-h(v)\ge 0,\forall (u,v)$. Notice $w(u,v)+h(u)\ge h(v)$. And triangle equality says $w(u,v)+\delta(s,u)\ge \delta(s,v)$. Therefore by taking $h:v \rightarrow \delta(s,v)$, we can transform $G$ into nonnegtive weight graph and all shortest paths are preserved.

-----

**Algorithm:**
Step 1. Graph maybe unconnected so we add a supernode $s$ to compute SSSP $\delta(s,v),\forall v\in V$. $G$ may contain negtive weight cycles, so Bellman-Ford is our only choice --> $\text{O}(|V||E|)$.
Step 2. If detect negtive weight cycles in step 1, abort. Otherwise make a new graph $G'$ from $G$ by reweighting graph weights accoridng to:

$$
    w'(u,v)=w(u,v)+\delta(s,u)-\delta(s,v)
$$

Step 3. $\forall s\in V$, compute SSSP in $G'$ using Dijkstra. The $\delta(s,v),\forall v\in V$ in original graph $G$ can be computed by following shortest path tree on $G'$. --> $\text{O}(|V|\cdot(|V|\log |V|+|E|+|V|+|E|))=\text{O}(|V|^2\log |V|+|V||E|)$

-----
**Analysis:**
Johnson's Algorithm takes $\text{O}(|V|^2\log |V|+|V||E|)$.