### Restaurant Lineup
Database is initialized with two empty data structures: a hash table $H$ and a linked list $L$. The link list maintain the customers in the waitlist in their arriving order. We always add the new customer to the back of $L$ and also in set $H$. Combined they take $\Theta(1)+1_{(a)}$. To seat the earliest customer we just remove name from the front of $L$ and also delete item in $H$. That is $\Theta(1)+1_{(a)(e)}$ in time.
Each record in Hash table is keyed at customer name and stores the reference to node in the linked list containing the customer. If the restaurant wish to remove someone from that waitlist, just find the name $x$ in $H$, follow $H[x]$ to certain node in $L$, delete that node, and finally delete $H[x]$, which take $1_{(e)}+\Theta(1)+ 1_{(a)}$.
|Operation|Running Time
|---|---
|build()|1
|add_name(x)|1(amortized)
|remove_name(x)|1(amortized)(expected)
|seat()|1(amortized)(expected)

### Rainy Research -- One-sided Range Query Example
Database should be a SET AVL $A$ mapping latitudes to AVL trees. i.e. each node in $A$ kayed on lattitude $l$ is an AVL tree $A(l)$ that stores measurements at $l$, which mapps time $t$s to rainfall measurements $l$s. For each AVL tree $A(l)$, augment each node $x$ with additional subtree property $x.max$ which is the maximum value of $r$ in subtree rooted at $x$. Because $x.max$ can be easily obtained using just properties in its descendants, we know it can be maintained in insert/delete procedure without affecting asymptotic performance.
To implement $\text{record\_data}(r,l,t)$, find $A(l)$ in $A$, create a new tree node keyed at $t$ and attached with rainfall value $r$, insert into tree $A(l)$. 
To implement $\text{peak\_rainfall(l,t)}$, we first find $A(l)$ which is tree $T$. We evaluate max rainfall in $T$ with keys bigger than $t$ by searching for $t$.
```C++
peak_rainfall(T, t):
    x = T.root
    peak = 0
    while T.nil != x:
        if t == x.key:
            peak = max(peak, x.r, x.right.max)
            return peak
        else if t > x.key:
            x = x.right
        else:
            peak = max(peak, x.r, x.right.max)
            x = x.left
    return peak
```
For two-sided range query, see problem session 4-5.
