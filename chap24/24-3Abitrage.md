**a.**
**Solution:**
$$
R[i_1,i_2]\cdot R[i_2,i_3]\cdot ... \cdot R[i_{k-1},i_k]\cdot R[i_k,i_1]>1
\\ \Rightarrow \log \frac{1}{R[i_1,i_2]}+\log \frac{1}{R[i_2,i_3]}+ ... + \log \frac{1}{R[i_{k-1},i_k]} +\log \frac{1}{R[i_k,i_1]}<0

$$

Construct new table $R'$ by transfroming all entries in $R$ : $R'[i][j]=\log \frac{1}{R[i][j]}$.
Use bellmanford to detect negtive weight cycles in $\text{O}(|V||E|)=\text{O}(n^3)$.

**b.**
Start from any witness and follow $pi$ attributes back. It does not lead to source $s$ any more but the negtive weight cycle.
refer to 24.1-6