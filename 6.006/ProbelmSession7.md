### Problem 7-3. Under Games ⭐
**Input:**
    connected graph $G=(V,E)$
    $E$ is $n$ bidirectional pipes $|E|=|V|=\text{O}(n)$
    positive integer edge weights
    some vertices marked as motion sensors with unknown sensitivity $k^*$
**Output:**
    Find a path from $source$ to $target$ without falling in range $k^*$ of any sensor in $\text{O}(n\log n) time$.

**Idea 1:** If we do know the sensitivity $k^*$, then by removing all the vertices within $k^*$ distance to any sensor the problem becomes a reachability problem which we can solve in linear time.

**Idea 2:** How do we recognize all the vertices within $k^*$ distance to any of the sensors? The answer is to add one Supernode $s$ that connects to all the sensors with edge weight zero, then compute SSSP from $s$ to other vertices.

**Algorithm:**
1. Compute SSSP from $s$ other vertices.
2. Order vertices $V$ by their $\delta(s,v), v \in V$
3. Use binary search on ordered vertices and repeatedly choose the middle one $u$. If after removing all vertices whose $\delta(s,v) \le \delta(s,u), v \in V$, $source \not \leadsto target$, try smaller distance; otherwise try bigger values until we find the biggest $k$ such that after removing all vertices whose $\delta(s,v) \le k$, $source \leadsto target$. Note that $k$ not necessarily equals to $k^*$.
4. Return such path.

**Analysis:**
SSSP by Dijkstra takes $\text{O}(|V|\log |V| + |E|)=\text{O}(n\log n)$ in Step 1; Sorting in Step 2 takes $\text{O}(|V|\log|V|)=\text{O}(n\log n)$; Binary Search repeats at most $\log |V|$ times and each time reachability can be computed using dfs in $\text{O}(n)$ time. Total time for algorithm is $\text{O}(n\log n)$.

### Problem 7-4. Critter Collection ⭐⭐
**Input:**
    $n$ vertices,one $source$,one $target$
    $|E|\le {{5n}\over {2}}=\text{O}(n)$
    each two-way trail $t$ has length $l_t>0$ and capacity $c_t>0$
    greedly collect every critter
    sad if $c_t>\text{empty Pocket Spheres}$
    critters will respawn to max capacity $c_t$ after collected
    Stores will empty backpack to $k$ Pocket Spheres
**Output:**
    Shortest path from $source$ to $target$ without ever being sad in $\text{O}(nk \log(nk))$ time.

**Idea:** Reconstruct a **Layered Graph**
A layered graph is in some sense like a state machine. We want to encompass into the graph the state information about the number of empty Pocket Spheres Ashley has when at some clearing spot. The layered graph $G'$ is built upon original graph $G$ by making it $K+1$ layers where layer $i$ represents arriving at some clearing spot with $i$ empty Pocket Spheres. $i$ ranges from $0$ to $k$. When Ashley traverses trail $t$ with capacity $c_t$ she needs to have at least $c_t$ empty Pockets Spheres otherwise she will be sad. And she must arrive at some lower level of the graph since $c_t>0$. Also when arriving at a store the state will immediately transit to the highest level of the graph that is there is an edge in $G'$ pointing upwards to level $k$ at same clearing. Unlike layered graph in Bellman-ford application in this case there are both edges pointing to upper layers and lower layers. So it's not a DAG.
**Algorithm:**
1. Represent each clearing with $k+1$ vertices $v_{c,i}, 0\le i\le k$. For each trail $c=(a,b)$, if a is a store, add one edge $(v_{a,k}),v_{b,k-c_t}$ (if $c_t > k$, return that sadness is unavoidable); Otherwise add edges $(v_{a,i},v_{b,i-c_t}), \forall i\ge c_t$. For each vertex $a$ with store, add edges $(v_{a.i},v_{a,k}),\forall 0\le i< k$.
2. Do Dijkstra from $v_{source,k}$.
3. Find minimum $\delta(s,v_{target,i}),0\le i\le k$ and return corresponding SSSP. If none of the $v_{target,i}$ is reachable, return asdness is unavoidable.

**Analysis:**
It takes $\text{O}(k|V|+k|E|)=\text{O}(kn)$ to construct layered graph in step 1; $|V'|=(k+1)n=\text{O}(kn)$ and $|E'|=\text{O}(k|E|)=\text{O}(kn)$.

It takes $\text{O}(|V'|\log |V'| + |E'|)=\text{O}(kn\log (kn))$ to perform Dijkstra in step2; 

It takes $\text{O}(k)$ to do final clearing in step 3. Combined algorithm takes $\text{O}(kn\log (kn))$.
