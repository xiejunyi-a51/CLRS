### Minimum Spanning Tree

**Def.**
1. Tree is an undirected acyclic connected graph.
2. Spanning tree is a tree that has the same vertex set as original graph $G=(V,E)$.
3. Minimum Spanning tree looks for minimum edge weights sum $\min W(T)=\min\sum_{(e\in T)}w(e)$.

**Edge Contraction Algorithm:**
1. create a new tree $T=(V,E_T)$, $E_T$ is initially empty.
2. For $i=1 \to |V|-1$: 
    Add in $T$ the minimum-weight edge $e$ in $G$. 
    Update $G$ by performing edge contraction of $e$.

**Prove Greedy Choice Property**
Let $w(x,y)=\min_{(u,v\in E)}w(u,v)$. Let $T^*$ be any MST on $G$. Assume it does not contain $(x,y)$. By the definition of tree. there is one and one only path between $x$ and $y$: $p=x \leftrightsquigarrow y$. Constrcut a new $T'$ by deleting any edge $(u,v)$ on $p$ and add $(x,y)$. 
Since $u,v$ is now connected via a path across edge $(x,y)$, any pair of vertices that used to connect via a path through edge $(u,v)$ is still connected. Because $T'$ is a connected graph with $|V|$ points and $|V|-1$ edges, $T'$ is a spanning tree. $W(T')=W(T)-w(u,v)+w(x,y)\le W(T)$. Therefore $T'$ is optimal and we proved there must be some MST on $G$ that constains $(x,y)$.

**Prove Optimal Substructure**
Let $w(x,y)=\min_{(u,v\in E)}w(u,v)$, and $G'$ be $G$ with $(x,y)$ removed and vertex $z$ added, so that $G'=(V',E')$.

 $$
 V'=V-\{x,y\}\cup z
 \\
 \hat V=\{j|(j,x)\in E\}\cup\{j|(j,y)\in E\}
 \\
 \hat E = \{(j,x)\in E\}\cup\{(j,y)\in E\}
 \\
 E'=E-\hat E+\{(j,z)|j\in \hat V\}.
 $$

Assume $T'$ is a MST on $G'$. Let graph $\tilde T=(\tilde V,\tilde E)$ be $T'$ with vertex $z$ replaced by edge $(x,y)$. We now prove that there must be one MST on $G$ that is equal to $\tilde T$.

Notice

$$
 V'=V-\{u,v\}\cup z
 \\
\Rightarrow V=  V'-z+\{u,v\}=\tilde V,
$$

graph $\tilde T$ covers $V$ with $|V'|-1+1=|V|-1$ edges. Therefore $\tilde T$ is at least a spannning tree on $G$.

$$
W(\tilde T)=W(T')+w(x,y)
$$

Suppose $\tilde T$ is not minimum spanning tree on $G$, there exists optimal $T''$ with $W(T'')<W(\tilde T)$. WLOG, $T''$ contains edge $(x,y)$. Let $T'''$ be $T''$ with $(x,y)$ replaced by $z$. $W(T'')=W(T''')+w(x,y)$. Then

$$
\begin{aligned}
W(T''')+w(x,y)=W(T'')&<W(\tilde T)=W(T')+w(x,y)
\\
W(T''')&<W(T'),
\end{aligned}
$$

which conflicts with $T'$ being MST on $G'$. Therefore we conclude MST on $G$ is composed of a greedy choice and MST on $G'$.

**Analysis:**
Each edge contraction takes $\text{O}(|V|)$ time. Naive algorithm performs total $|V|-1$ times edge contraction and has runnning time $\text{O}(|V|^2)$.

**Improve efficiency:**
What if we don't perform actual edge contraction each time but simply keep track of which edges are in which components? This way, for any edge $e$:
1. Either $e$ connects two CC (two endpoints in diffferent CC). $e$ exists in the conceptual contracted graph therefore available for greedy choice.
2. Or $e$ lies in one CC. $e$ is already removed in the conceptual contracted graph.

**Kruskal's Algorithm:**
1. create a new tree $T=(V,E_T)$, $E_T$ is initially empty. 
Sort $E$ in increasing order in $\text{O}(|E|\log|E|)=\text{O}(|E|\log|V|)$.
for each vertex $v\in V$, $MakeSet(v)$.
2. for each edge $(u,v)\in E$:
    if $FindSet(u)!=FindSet(v)$:
    Add $(u,v)$ in $T$
    $Union(u,v)$

**Analysis:**
A series of $|E|+|V|$ $MakeSet/FindSet/Union$ operations, in which $|V|$ $MakeSet$. Total runnning time is $\text{O}(|E|+\alpha(|V|))$. Together with sorting $E$, Kruskal's takes runnning time $\text{O}(|E|\log |V|)$.

**Correctness:**
Prove Kruskal's algorithm builds exactly the same MST as naive edge contraction algorithm.

Let edges $e_1,...,e_{|E|}$ be edges in monotonically weight increasing order. Assume Kruskal's algo chooses the same edges as edge contraction algo for first $j$ steps. Let edge $e_m$ be the last chosen.
By definition $e_m$ is the minimum-weight edge in contracted graph $G'$, after contracting $m$, $G'$ only contains edges $e_p,...,e_q$ in weight increasing order, $p>m$. Then $e_p$ is the next edge for edge contraction algo.
Assume Kruskal's will add in MST $e_o=(x,y)$ in $j+1$ step. Then $x,y$ are in different CC in $T$, $(x,y)$ exists in $G'$. Since $G'$ only contains edges $e_p,...,e_q$, it must be $o\ge p$. If $o>p$, Kruskal's decided $e_p$ lies in one CC, which conflicts with $e_p$ exists in $G'$. Therefore it must be $e_o=e_p$.
