### Problem 6-1 Topological Training
Given a directed acyclic graph $G=(V,E)$
a. Number of distinct topological orserings of $G$ is 8:

(4,2,1,0,3,5) (4,2,0,1,3,5) (4,2,0,3,1,5) (4,2,0,3,5,1) (4,2,1,0,5,3) (4,2,0,1,5,3) (4,2,0,5,1,3) (4,2,0,5,3,1)

b. Number of distinct single edges that could be added to G to construct a simple graph with no topological ordering is in fact total number of paths $(u,v)$ where $v$ is reachable from $u$:

$$
\sum_{\{u,v\in V\}: u \leadsto v} 1,
$$

because for each path $u\leadsto v$ we can add an edge $(v,u)$ and construct a cycle.

11.

### Problem 6-2 Never Return
Apply SSSP algorithm on DAG relaxation. Start from source "gorge" and compute SSSP to every other landmark outside and neighboring "Honor Stone". Choose the shortest path among destinations. The only question remaining is how to enforce the "Never Return" restriction. 
One solution could be pre-screening. First compute the Euclidean distance $x$ of every landmark from "gorge". Then for each trail $(u,v)$, disable or remove the edge from large distance landmark to smaller or equal distance in graph representation(but remain edge from other direction). Since there are only edges from smaller distance to larger, graph is DAG.

### Problem 6-3 DigBuild
Transform each conversion $(d_1,b_1,d_2,b_2)$ in set into proportional $(1,b_1,\frac{d_2}{d_1},b_2)$. Contruct a graph $G=(V,E)$. $V$ is the set of block type $b_i$. For each transformed conversion $(d_1,b_1,d_2,b_2)$ add an edge $(b_1,b_2)$ with weight $w(b_1,b_2)=\frac{d_2}{d_1}$. If there is any cycle in graph such that,

$$
\prod_{(u,v)\in C}w(u,v)>1,
$$

This set of conversions is disallowed. Because by going through this cycle over and over, number of blocks will explode. Users can generate infinite number of blocks of any type reachable from this cycle. In this game world however, we can't simply convert 1 $b_1$ block to $\frac{d_2}{d_1}$ $b_2$ block. We have to convert $d_1$ number of $b_1$ block in a batch. Since starting number of block of any type $D\ge d_i$, users have sufficient starting blocks for any block on the cycle. Because we want to compute maximum product for any cyclic path $u\leadsto u$, but the product of path can either become larger or smaller as we add more edges, Dijkstra does not apply here.

We can transform the conversion again into edge $b_1,b_2$ with weight $w'(b_1,b_2)=\log \frac{d_1}{d_2}$. Now the criterion for Invalid becomes:

$$
\prod_{(u,v)\in C}w(u,v)>1\\
\log \prod_{(u,v)\in C}w(u,v)>0\\
\sum_{(u,v)\in C}\log w(u,v)>0\\
\sum_{(u,v)\in C}-\log w(u,v)<0\\
\sum_{(u,v)\in C}\log \frac{1}{w(u,v)}<0\\
\sum_{(u,v)\in C}\log {w'(u,v)}<0.
$$

We can apply bellman-ford to detect negative-weight cycles in $\text{O}(VE)=\text{O}(n^3)$.

### Problem 6-4 Tipsy Tannister

### Problem 6-5 Cloud Computing
Build a graph $G=(V,E)$. $V=\{v_o \cup v_i|f_i\rightarrow v_i \forall f_i\}$ is the set of all code pieces to run plus one addtional supernode $v_o$ that connects to all 0-indegree vertices in $V$. For each dependency $(f_1,f_2)$, add an edge $(v_1,v_2)$ with weight $w(v_1,v_2)=f_2.t$. Also for each incident edge of $v_o$, $w(v_o,v)=v.t$.
*(a).*
Run dfs on $G$ to detect any cycle.
*(b).*
Perform topological sort on $V$. Run SSSP on DAG $G$ in topological sort order. and get $\max_{v\in V} \delta(v_o,v)$. Since $|D|=\Theta(|C|)$, $T=\Theta(|D|)$.
*(c).*
```C++
RELAX(u,v,w):
    if u.d + w(u,v) > v.d:
        v.d = u.d + w(u,v)
```