### 24-1 Yen’s improvement to Bellman-Ford

-----
a. 
Every path $v_i\leadsto v_j$ can only happen for $i<j$ for $G_f$ and $i>j$ for $G_b$. There is no way for a path to circle back to starting vertex. So both graph are acyclic. $v_1,v_2,...,v_{|V|}$ is valid topological sort for $G_f$ because for each edge $(v_i,v_j),i<j$, vertex $v_j$ is places after $v_i$. Samewise for $G_b$.

-----
b.
Assume SSSP $s\leadsto v$. If we segement $s\leadsto v$ into a list of subpaths $p_1,p_2,...,p_n$. the list atmost one strictly forwad going subpath, one strictly backward going subpath, and other subpaths are combinations of one forward and one backward subpath. With this scheme each pass over the edges can cover one segment of subpath. Since path length is atmost $|V|-1$,

$$
1+2(n-2)+1\le |V|-1,\\
1+2(n-1)\le |V|-1,\\
2n\le |V|-1\\
\Rightarrow n\le \frac{|V|-1}{2}.
$$

-----
c.
No. Run time is still $\text{O}(|E||V|)$.