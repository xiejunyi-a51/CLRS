### 24-6 Bitonic shortest paths
Suppose that we are given a directed graph $G=(V,E)$ with weight function $w :E\rightarrow R$, where all edge weights are unique, and we wish to find single-source shortest paths from a source vertex s. We are given one additional piece of infor- mation: for each vertex $v\in V$, the weights of the edges along any shortest path from $s$ to $v$ form a bitonic sequence.

Give the most efficient algorithm you can to solve this problem, and analyze its running time.

**Solution:**
Because for each vertex $v\in V$, edges weights along shortest path from $s$ to $v$ form a bitonic sequence, we
know shortest path has finite edges and no negtive weight cycles in $G$. But bellman-ford is still our only choice here since there may exist negtive edge weights. We will carefully choose the order to relax edges: in increasing edge weight order, then decreasing edge weight order, then increasing, then decreasing. A total of 4 rounds.

Observe that for bitonic sequence, there can be atmost three monotonic increasing/decreasing segments, in which the ranges of two possible increasing/decreasing segments do not overlap. That is for any shortest path $s
\stackrel{p}\leadsto v, v\in V$, such 4 rounds of relaxation will relax all $(u,v)\in p$ in order. And by path relaxation
property, $v.d=\delta(s,v)$. 

Running time is the time to sort edge weights plus 4 times relaxation : $\text{O}(E\log
E)+\text{O}(4*E)=\text{O}(E\log E)$