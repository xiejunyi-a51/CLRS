Explain how to implement doubly linked lists using only one pointer value $x.np$ per item instead of the usual two ($next$ and $prev$). Assume all pointer values can be interpreted as $k$-bit integers, and define $x.np$ to be $x.np = x.next \text{ XOR } x.prev$, the $k$-bit "exclusive-or" of $x.next$ and $x.prev$. (The value $\text{NIL}$ is represented by $0$.) Be sure to describe what information you need to access the head of the list. Show how to implement the $\text{SEARCH}$, $\text{INSERT}$, and $\text{DELETE}$ operations on such a list. Also show how to reverse such a list in $O(1)$ time.
**Solution:**
- Insert:
Make a new node of address $p$ whose xor $np$ field equals $0 \oplus L.head$ and insert as new head of list. Now if second node $y$ exists, change its $np=p\oplus y.next$.
- Search:
Starting from $L.head$, traverse through the list by each time get next node address $p=p.prev \oplus p.np$.
- Delete:
To delete $y$, We have to traverse the list to find its predessor $x$ first. Then its successor $z=x\oplus y.np$. Make $x.np=x.np\oplus y\oplus z$, $z.np=z.np\oplus y\oplus x$.
- Reverse:
Swap L.head and L.tail.