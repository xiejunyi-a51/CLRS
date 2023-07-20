### Longest monotonically increasing Subsequence Problem


Assume at some point $a_1,a_2,...,a_m$ has the smallest ending element among all length-$m$ increasing subsequence and $b_1,b_2,...,b_n$ has the smallest ending element among all length-$n$ increasing subsequence. $m > n \Leftrightarrow a_m > b_n$.
**Proof:**

$\Rightarrow$ If $m>n$ and $a_m\le b_n$, then subsequence $a_1,a_2,...,a_n$ will be a length-$n$ increasing subsequence with smaller ending element $a_n$. Contradicts with assumption. By proof of contradiction, if $m>n$ then $a_m> b_n$.

$\Leftarrow$ Similarly if $a_m>b_n$ and $m<n$, then subsequence $b_1,b_2,...,b_m$ will be a length-$m$ increasing subsequence with smaller ending element $b_m$, By proof of contradiction, if  $a_m> b_n$ then $m>n$.

**Algorithm:**
For each $A[i]$, find LMIS ending with $A[i](LMIS(i))$, return $LMIS(\argmax_{i} |LMIS(i)|) $.
To calculate $LMIS(i)$, assume we already know $LMIS(0),...,LMIS(i-1)$. Let $maxLMIS =\max LMIS(j),j < i$. Also keep record of smallest ending elements for LMIS of length 1 to $maxLMIS$, which is in sorted order. Binary search for largest ending element smaller than $A[i]$, which leads to longest $LMIS(j)$ that satisfies. Add one to its size.
